#!/usr/bin/env bash
set -euo pipefail

LLVM_PREFIX="${LLVM_PREFIX:-/opt/homebrew/opt/llvm@21}"
CC="${CC:-gcc}"
CFLAGS="${CFLAGS:--I$LLVM_PREFIX/include -L$LLVM_PREFIX/lib -lLLVM}"
OPT="${OPT:--O2}"
BOOTSTRAP="${BOOTSTRAP:-./CCkai}"
SRC="src/compiler.kai"
OUT_C="compiler.c"
OUT_CC="CCcompiler.c"

echo "=== Kai Bootstrap ==="
echo "  BOOTSTRAP: $BOOTSTRAP"
echo "  CC:        $CC"
echo "  CFLAGS:    $CFLAGS"
echo "  OPT:       $OPT"
echo ""

# --- helper: save reference outputs ---
save_ref() {
  cp "$1" "$1.ref"
}
check_identity() {
  local label="$1" file="$2"
  local old=$(shasum "$file.ref" | cut -d' ' -f1)
  local new=$(shasum "$file"     | cut -d' ' -f1)
  if [ "$old" = "$new" ]; then
    echo "  ✅ $label: identical (shasum: $old)"
  else
    echo "  ⚠️  $label: DIFFERS"
    echo "     stage1: $old"
    echo "     stage2: $new"
  fi
}

# --- 1. legacy (-c) path ---
echo "--- Stage 1: legacy codegen (-c) ---"
$BOOTSTRAP -c "$SRC"
save_ref "$OUT_C"
$CC $CFLAGS $OPT -o CCkai-stage1 "$OUT_C"
echo "  → CCkai-stage1 ($(stat -f%z CCkai-stage1) bytes)"
echo ""

# --- 2. builder (-CC) path ---
echo "--- Stage 1: builder codegen (-CC) ---"
$BOOTSTRAP -c -CC "$SRC"
save_ref "$OUT_CC"
$CC $CFLAGS $OPT -o CCkai-stage1-CC "$OUT_CC"
echo "  → CCkai-stage1-CC ($(stat -f%z CCkai-stage1-CC) bytes)"
echo ""

# --- 3. Self-hosting: stage1-CC compiles itself ---
echo "--- Stage 2 (self-host): builder (-CC) ---"
./CCkai-stage1-CC -c -CC "$SRC"
$CC $CFLAGS $OPT -o CCkai-stage2-self "$OUT_CC"
echo "  → CCkai-stage2-self ($(stat -f%z CCkai-stage2-self) bytes)"
echo ""

# --- 3. Self-hosting: stage1-CC compiles itself ---
echo "--- Stage 3 (self-host): builder (-CC) ---"
./CCkai-stage2-self -c -CC "$SRC"
$CC $CFLAGS $OPT -o CCkai-stage3-self "$OUT_CC"
echo "  → CCkai-stage3-self ($(stat -f%z CCkai-stage3-self) bytes)"
echo ""

# --- 4. Self-hosting: stage1-CC compiles via legacy ---
echo "--- Stage 2 (self-host): legacy (-c) ---"
./CCkai-stage1-CC -c "$SRC"
$CC $CFLAGS $OPT -o CCkai-stage2-legacy "$OUT_C"
echo "  → CCkai-stage2-legacy ($(stat -f%z CCkai-stage2-legacy) bytes)"
echo ""

# --- 5. Identity check (same-path cross-generation) ---
echo "--- Self-hosting identity checks ---"
check_identity "legacy (-c) cross-gen" "$OUT_C"
check_identity "builder (-CC) cross-gen" "$OUT_CC"
echo ""

# --- 6. Binary sizes ---
echo "--- Binary sizes ---"
for bin in CCkai-stage1 CCkai-stage1-CC CCkai-stage2-self CCkai-stage3-self CCkai-stage2-legacy; do
  printf "  %-24s %'d bytes\n" "$bin" "$(stat -f%z "$bin")"
done
echo ""

# --- 7. Cleanup ---
rm -f "$OUT_C.ref" "$OUT_CC.ref"

echo "=== Done ==="
