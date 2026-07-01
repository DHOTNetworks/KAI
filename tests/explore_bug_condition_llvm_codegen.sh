#!/bin/bash
# Bug Condition Exploration Test — llvm-codegen-fix spec, Task 1
#
# Property 1: Bug Condition - `_kai_str_concat` Invalid Parameter Addressing /
#             Struct-by-Value Return Mismatch / Local Var From sret Call
# Validates: Requirements 1.11, 1.12, 1.13
#
# This script is the reproducible exploration test referenced by design.md's
# isBugConditionA/B/C predicates. It is EXPECTED TO FAIL (reproduce the defect)
# on unfixed src/codegen_llvm.kai. Tasks 3.2, 4.5, 5.2 re-run this SAME script
# after each defect fix to confirm the corresponding portion now passes.
#
# Usage: ./tests/explore_bug_condition_llvm_codegen.sh
# Exit code: 0 if ALL of Defect A / B / C checks pass (fixed), non-zero if any
#            defect is still present (unfixed / bug reproduced).

set -u
cd "$(dirname "$0")/.." || exit 1

WORKDIR="$(mktemp -d)"
trap 'rm -rf "$WORKDIR"' EXIT

FAIL=0
pass() { echo "  [PASS] $1"; }
fail() { echo "  [FAIL] $1"; FAIL=1; }

echo "== Step 0: Ensure kai_bootstrap exists =="
if [ ! -x ./kai_bootstrap ]; then
    echo "kai_bootstrap not found or not executable at ./kai_bootstrap"
    exit 2
fi
pass "kai_bootstrap present"

echo "== Step 1: Build compiler binary from src/compiler.kai via kai_bootstrap (unfixed src under test) =="
./kai_bootstrap src/compiler.kai > "$WORKDIR/bootstrap_build.log" 2>&1
if [ ! -x ./compiler ]; then
    echo "Failed to build ./compiler via kai_bootstrap. See log:"
    cat "$WORKDIR/bootstrap_build.log"
    exit 2
fi
pass "./compiler built from src/compiler.kai (includes src/codegen_llvm.kai under test)"

echo "== Step 2: Emit LLVM IR for tests/test_all_features.kai =="
rm -f test_all_features.ll
./compiler tests/test_all_features.kai -emit-llvm -c > "$WORKDIR/emit.log" 2>&1
if [ ! -f test_all_features.ll ]; then
    echo "Failed to emit test_all_features.ll. See log:"
    cat "$WORKDIR/emit.log"
    exit 2
fi
cp test_all_features.ll "$WORKDIR/test_all_features.ll"
pass "Emitted test_all_features.ll ($(wc -l < test_all_features.ll | tr -d ' ') lines)"

echo
echo "== Defect A check: _kai_str_concat invalid address-of SSA parameter (isBugConditionA) =="
STRCONCAT_BODY=$(awk '/^define ptr @_kai_str_concat/,/^}/' "$WORKDIR/test_all_features.ll")
echo "$STRCONCAT_BODY" | sed 's/^/    /'
if echo "$STRCONCAT_BODY" | grep -Eq 'call i64 @strlen\(ptr %[a-zA-Z0-9_]+\)'; then
    pass "_kai_str_concat calls strlen directly on the SSA parameter (no address-of observed in emitted IR)"
else
    fail "_kai_str_concat does NOT call strlen directly on the SSA parameter value (Defect A pattern present)"
fi

echo
echo "== Defect B check: struct-by-value return signature vs call-site mismatch (isBugConditionB) =="
SB_INIT_DEF=$(grep -E '^define .*@StringBuilder_init\(' "$WORKDIR/test_all_features.ll")
SB_INIT_CALLS=$(grep -E 'call ptr @StringBuilder_init\(' "$WORKDIR/test_all_features.ll")
echo "  Declared signature: $SB_INIT_DEF"
echo "  Call site(s):"
echo "$SB_INIT_CALLS" | sed 's/^/    /'
DECL_ARGS=$(echo "$SB_INIT_DEF" | grep -o '(' | wc -l) # unused, just structural note
DECL_PARAM_COUNT=$(echo "$SB_INIT_DEF" | grep -oE '\(.*\)' | tr ',' '\n' | grep -c 'ptr')
CALL_ARG_COUNT=$(echo "$SB_INIT_CALLS" | head -1 | grep -oE '\(.*\)' | tr ',' '\n' | grep -c 'ptr')
DECL_RET=$(echo "$SB_INIT_DEF" | grep -oE 'define (ptr|void)' | awk '{print $2}')
if [ "$DECL_PARAM_COUNT" -gt 0 ] && [ "$DECL_PARAM_COUNT" = "$CALL_ARG_COUNT" ] && [ "$DECL_RET" = "void" ]; then
    pass "StringBuilder_init uses sret (void return, matching call-site arg count)"
else
    fail "StringBuilder_init signature ($DECL_PARAM_COUNT ptr params, returns $DECL_RET) does not match sret convention / mismatches call-site arg count ($CALL_ARG_COUNT)"
fi

echo
echo "== Defect C check: 'var allocator = KaiAllocator_init()' produces a valid stack address (isBugConditionC) =="
INT_TO_STR_BODY=$(awk '/^define ptr @int_to_str/,/^}/' "$WORKDIR/test_all_features.ll")
ALLOC_INIT_LINE=$(echo "$INT_TO_STR_BODY" | grep -E 'call ptr @KaiAllocator_init')
echo "  int_to_str's KaiAllocator_init call: $ALLOC_INIT_LINE"
if echo "$ALLOC_INIT_LINE" | grep -qE 'call ptr @KaiAllocator_init\(ptr %struct_init\)' && echo "$INT_TO_STR_BODY" | grep -q 'define void @KaiAllocator_init' ; then
    pass "KaiAllocator_init call site passes a real alloca as sret slot"
else
    fail "KaiAllocator_init call site does not use a proper sret alloca (local var decl mistreats call result as pointer)"
fi

echo
echo "== End-to-end check: clang-compile emitted IR and run Point.describe() (Trait check:) =="
if clang "$WORKDIR/test_all_features.ll" -o "$WORKDIR/test_all_features_bin" > "$WORKDIR/clang.log" 2>&1; then
    pass "clang accepted the emitted IR"
else
    fail "clang failed to compile emitted IR"
    cat "$WORKDIR/clang.log"
fi

if [ -x "$WORKDIR/test_all_features_bin" ]; then
    OUTPUT=$("$WORKDIR/test_all_features_bin" 2>&1)
    STATUS=$?
    echo "  Program output:"
    echo "$OUTPUT" | sed 's/^/    /'
    echo "  Exit status: $STATUS"
    if [ "$STATUS" -ne 0 ]; then
        fail "Native binary crashed (exit $STATUS) while running Point.describe() / Trait check"
    elif echo "$OUTPUT" | grep -q "Point(3, 4)"; then
        pass "Trait check line printed correct 'Point(3, 4)' output"
    else
        fail "Trait check line did not print expected 'Point(3, 4)' output (garbled output)"
    fi
fi

echo
if [ "$FAIL" -ne 0 ]; then
    echo "RESULT: Bug condition REPRODUCED (one or more defects present). This is the expected outcome on unfixed code."
    exit 1
else
    echo "RESULT: No defects detected — all checks passed."
    exit 0
fi
