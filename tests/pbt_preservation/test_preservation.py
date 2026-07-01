"""
Preservation property tests for the llvm-codegen-fix bugfix spec (Task 2).

**Validates: Requirements 3.11, 3.12, 3.13**

These tests are run BEFORE the fix is implemented (Defects A, B, C in
src/codegen_llvm.kai are still present). They capture the *observed* IR-shape
baseline for code paths that the fix must NOT change:

  - Property 4 (design.md) - Preservation: Non-Struct-Returning Calls and
    Direct Struct Init Unaffected.
      * Calls to functions/methods whose return type is a primitive, Void,
        pointer (*T), reference (&T), or enum value type must continue to
        use the direct-return calling convention (no hidden sret pointer
        parameter prepended to the signature, no extra stack slot allocated
        and prepended to the call's argument list).
      * Direct `ek_struct_init` construction (e.g. `Point(x: 3, y: 4)`) must
        continue to be lowered as alloca + (GEP + store)-per-field with the
        alloca pointer as the resulting value, with NO function call
        involved at all.
      * Non-`_kai_str_concat` runtime helper calls (`strcmp` for Str
        equality, `printf` for `print_*`) must continue to build their
        argument arrays exactly as today (direct SSA values, not addresses
        of temporaries).

The tests drive the REAL self-hosting pipeline: the unfixed `src/compiler.kai`
(built by `kai_bootstrap` into `kai_unfixed`) compiles small generated `.kai`
programs with `-emit-llvm -c`, and the resulting `.ll` text is inspected for
the IR-shape patterns above via targeted regex assertions (a structural
diff against a hand-written expected snippet, not a full IR interpreter -
appropriate here because we are asserting the ABSENCE of new constructs the
fix will introduce, and the PRESENCE of exact call/alloca shapes that exist
today).

EXPECTED OUTCOME on unfixed code: ALL tests PASS. This is not a bug
reproduction test (that is Task 1) - it establishes the regression baseline
that Tasks 3-5 (the fix implementation) must not break.
"""

import os
import re
import shutil
import subprocess
import tempfile
import uuid

import pytest
from hypothesis import HealthCheck, given, settings
from hypothesis import strategies as st

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
COMPILER_BIN = os.path.join(REPO_ROOT, "kai_unfixed")

# Kai primitive/pointer/reference type categories a function/method can
# return without triggering the struct-by-value sret path (per Preservation
# Requirements in design.md: "Calls to functions returning Int, Str, Bool,
# Float, Void, *T, &T, or enum value types").
PRIMITIVE_RETURN_TYPES = ["Int", "Bool", "Char", "Float", "Str"]


def _require_compiler():
    if not os.path.isfile(COMPILER_BIN):
        pytest.skip(
            f"unfixed compiler binary not found at {COMPILER_BIN}; "
            "build it with `./kai_bootstrap src/compiler.kai -o ./kai_unfixed`"
        )


def compile_kai_source(source: str) -> str:
    """
    Writes `source` to a fresh temp directory, compiles it with the unfixed
    kai compiler using `-emit-llvm -c` (emit .ll, skip clang link), and
    returns the emitted LLVM IR text.

    Each call gets its own temp directory since the compiler always writes
    the output `.ll` next to the process's CWD using the input file's base
    name (see get_base_name/compiler.kai), regardless of the input path.
    """
    _require_compiler()
    tmpdir = tempfile.mkdtemp(prefix="kai_pbt_")
    try:
        src_name = f"prog_{uuid.uuid4().hex[:8]}"
        src_path = os.path.join(tmpdir, src_name + ".kai")
        with open(src_path, "w") as f:
            f.write(source)

        result = subprocess.run(
            [COMPILER_BIN, src_path, "-emit-llvm", "-c", "-o", src_name],
            cwd=tmpdir,
            capture_output=True,
            text=True,
            timeout=30,
        )
        ll_path = os.path.join(tmpdir, src_name + ".ll")
        assert result.returncode == 0, (
            f"unfixed compiler failed to compile generated program "
            f"(exit {result.returncode}):\nSTDOUT:\n{result.stdout}\n"
            f"STDERR:\n{result.stderr}\nSOURCE:\n{source}"
        )
        assert os.path.isfile(ll_path), (
            f"expected .ll output at {ll_path} was not produced.\n"
            f"SOURCE:\n{source}"
        )
        with open(ll_path) as f:
            return f.read()
    finally:
        shutil.rmtree(tmpdir, ignore_errors=True)


def kai_param_decl(ktype: str, name: str) -> str:
    if ktype == "*Int":
        return f"{name}: *Int"
    return f"{name}: {ktype}"


def kai_literal_for(ktype: str) -> str:
    return {
        "Int": "1",
        "Bool": "true",
        "Char": "'a'",
        "Float": "1.5",
        "Str": '"x"',
    }[ktype]


# ============================================================================
# Property 4a: non-struct-returning free function calls
# ============================================================================


@settings(
    max_examples=25,
    deadline=None,
    suppress_health_check=[HealthCheck.too_slow, HealthCheck.function_scoped_fixture],
)
@given(
    return_types=st.lists(
        st.sampled_from(PRIMITIVE_RETURN_TYPES), min_size=1, max_size=5
    )
)
def test_preservation_non_struct_returning_function_calls(return_types):
    """
    **Validates: Requirements 3.11**

    For any function whose Kai return type is Int/Bool/Char/Float/Str (i.e.
    NOT a registered struct name), the emitted LLVM function signature must:
      - take exactly as many parameters as declared (no leading hidden sret
        pointer parameter prepended)
      - return the mapped LLVM type directly via `ret <ty> ...` (not `void`
        with the result written through a pointer)

    And every call site must:
      - call the function with exactly the declared argument count (no
        extra alloca'd stack slot prepended to the argument list)
    """
    lines = []
    call_lines = []
    for i, rt in enumerate(return_types):
        fname = f"fn_{i}"
        lit = kai_literal_for(rt)
        lines.append(f"fn {fname}(p0: {rt}) -> {rt} {{")
        lines.append("    return p0")
        lines.append("}")
        call_lines.append(f"    let r{i} = {fname}({lit})")

    body = "\n".join(lines)
    calls = "\n".join(call_lines)
    source = f"""{body}

fn main() -> Int {{
{calls}
    print_int(1)
    return 0
}}
"""
    ir = compile_kai_source(source)

    ret_ll_map = {
        "Int": "i64",
        "Bool": "i64",
        "Char": "i8",
        "Float": "double",
        "Str": "ptr",
    }

    for i, rt in enumerate(return_types):
        fname = f"fn_{i}"
        expected_ret_ll = ret_ll_map[rt]

        # Signature: exactly ONE parameter (no hidden sret pointer prepended),
        # and the LLVM return type matches the direct (non-void, non-sret) mapping.
        define_pattern = re.compile(
            rf"^define\s+{re.escape(expected_ret_ll)}\s+@{re.escape(fname)}\("
            rf"[^,)]*\)\s*\{{",
            re.MULTILINE,
        )
        assert define_pattern.search(ir), (
            f"Expected direct-return signature `define {expected_ret_ll} "
            f"@{fname}(<1 param>)` (no sret) not found for return type "
            f"{rt!r}.\nIR:\n{ir}"
        )

        # Body must terminate with `ret <ty> ...` (not `ret void` writing
        # through a pointer).
        body_match = re.search(
            rf"define\s+{re.escape(expected_ret_ll)}\s+@{re.escape(fname)}\(.*?\n(.*?)\n\}}",
            ir,
            re.DOTALL,
        )
        assert body_match, f"Could not locate body for {fname}.\nIR:\n{ir}"
        assert re.search(
            rf"ret\s+{re.escape(expected_ret_ll)}\s", body_match.group(1)
        ), (
            f"Expected `ret {expected_ret_ll} ...` in body of {fname}, "
            f"found no direct return (possible sret regression).\n"
            f"Body:\n{body_match.group(1)}"
        )

        # Call site: exactly one argument passed, result used directly
        # (no extra alloca'd sret slot prepended as first argument).
        call_pattern = re.compile(
            rf"call\s+{re.escape(expected_ret_ll)}\s+@{re.escape(fname)}\(([^)]*)\)"
        )
        call_match = call_pattern.search(ir)
        assert call_match, (
            f"Expected direct call-site `call {expected_ret_ll} @{fname}(...)` "
            f"not found.\nIR:\n{ir}"
        )
        # Exactly one comma-separated argument (type + value), i.e. no
        # additional leading sret pointer argument.
        arg_str = call_match.group(1).strip()
        assert arg_str.count(",") == 0, (
            f"Expected exactly 1 argument at {fname}'s call site (no "
            f"prepended sret slot), got args: {arg_str!r}\nIR:\n{ir}"
        )


# ============================================================================
# Property 4b: non-struct-returning method calls
# ============================================================================


@settings(max_examples=10, deadline=None, suppress_health_check=[HealthCheck.too_slow])
@given(extra=st.integers(min_value=0, max_value=1000))
def test_preservation_non_struct_returning_method_calls(extra):
    """
    **Validates: Requirements 3.11**

    Method calls on struct types that return a non-struct type (Int here,
    standing in for the `KaiAllocator.alloc`-style case mentioned in
    design.md) must continue to pass `self` as the first argument and use
    the direct-return calling convention (no sret).
    """
    source = f"""struct Box {{
    val: Int
}}
impl Box {{
    fn get_val(self, extra: Int) -> Int {{
        return self.val + extra
    }}
}}
fn main() -> Int {{
    let b = Box(val: 10)
    let r = b.get_val({extra})
    print_int(r)
    return 0
}}
"""
    ir = compile_kai_source(source)

    # Signature unaffected: self ptr + 1 Int param, direct i64 return.
    assert re.search(
        r"define\s+i64\s+@Box_get_val\(ptr\s+%0,\s*i64\s+%1\)\s*\{", ir
    ), f"Box_get_val signature shape regressed (expected self+Int, direct i64 return).\nIR:\n{ir}"

    assert re.search(r"ret\s+i64\s+%add", ir), (
        f"Box_get_val body no longer directly returns via `ret i64` "
        f"(possible sret regression).\nIR:\n{ir}"
    )

    # Call site: self pointer + 1 arg = exactly 2 arguments, direct i64 call result.
    call_match = re.search(r"call\s+i64\s+@Box_get_val\(([^)]*)\)", ir)
    assert call_match, f"Expected direct method call-site not found.\nIR:\n{ir}"
    assert call_match.group(1).count(",") == 1, (
        f"Expected exactly 2 arguments (self, extra) at Box_get_val's call "
        f"site, got: {call_match.group(1)!r}\nIR:\n{ir}"
    )


# ============================================================================
# Property 4c: direct ek_struct_init construction
# ============================================================================


@settings(
    max_examples=25,
    deadline=None,
    suppress_health_check=[HealthCheck.too_slow, HealthCheck.function_scoped_fixture],
)
@given(
    field_values=st.lists(
        st.integers(min_value=-1000, max_value=1000), min_size=1, max_size=6
    )
)
def test_preservation_direct_struct_init(field_values):
    """
    **Validates: Requirements 3.12**

    `Point`-style direct struct construction via `ek_struct_init` (e.g.
    `Point(x: 3, y: 4)`) must continue to lower to a single
    `alloca` + one `getelementptr` + `store` pair per field, with the alloca
    pointer used directly as the resulting value - with NO function call
    anywhere in that construction sequence (it does not go through
    `register_func_decl`/`gen_func_body`/call machinery at all, so it is
    structurally unaffected by the sret fix regardless of field count).
    """
    n = len(field_values)
    struct_name = f"GenStruct{n}"
    fields_decl = "\n".join(f"    f{i}: Int" for i in range(n))
    fields_init = ", ".join(f"f{i}: {v}" for i, v in enumerate(field_values))

    source = f"""struct {struct_name} {{
{fields_decl}
}}
fn main() -> Int {{
    let g = {struct_name}({fields_init})
    print_int(1)
    return 0
}}
"""
    ir = compile_kai_source(source)

    # Must find: alloca %GenStructN, then N x (getelementptr + store), with
    # the alloca as a self-contained construction block (no call between
    # the alloca and its last store).
    alloca_match = re.search(
        rf"%struct_init\s*=\s*alloca\s+%{re.escape(struct_name)},[^\n]*\n(.*)",
        ir,
        re.DOTALL,
    )
    assert alloca_match, (
        f"Expected `%struct_init = alloca %{struct_name}, ...` not found - "
        f"direct struct-init lowering shape regressed.\nIR:\n{ir}"
    )

    following = alloca_match.group(1)
    # Take just the lines up to (and including) the last store that
    # references field_gep for this struct, before any other instruction
    # kind interrupts the sequence.
    field_gep_store_matches = list(
        re.finditer(
            r"%field_gep\d*\s*=\s*getelementptr[^\n]*\n\s*store[^\n]*", following
        )
    )
    assert len(field_gep_store_matches) >= n, (
        f"Expected {n} getelementptr+store field-init pairs directly after "
        f"the struct alloca, found {len(field_gep_store_matches)}.\nIR:\n{ir}"
    )

    # No `call` instruction may appear between the alloca and the Nth
    # field's store (direct construction must not involve any function call).
    # Scope strictly to the struct-init region: from the alloca up through
    # the end of the Nth (last) field_gep+store pair - NOT the rest of the
    # module, which may legitimately contain calls afterward (e.g. the
    # `print_int(1)` that follows the struct-init in the test program).
    last_field_pair_end = field_gep_store_matches[n - 1].end()
    prefix_upto_last_field = following[:last_field_pair_end]
    assert "call" not in prefix_upto_last_field, (
        f"Found a `call` instruction inside direct struct-init construction "
        f"for {struct_name} - this path must remain call-free.\nIR:\n{ir}"
    )


# ============================================================================
# Property 4d: non-_kai_str_concat runtime helper calls (strcmp, printf)
# ============================================================================


@settings(max_examples=10, deadline=None, suppress_health_check=[HealthCheck.too_slow])
@given(
    s1=st.text(alphabet=st.characters(whitelist_categories=("Ll",)), min_size=1, max_size=5),
    s2=st.text(alphabet=st.characters(whitelist_categories=("Ll",)), min_size=1, max_size=5),
)
def test_preservation_str_equality_uses_strcmp_directly(s1, s2):
    """
    **Validates: Requirements 3.13**

    `Str == Str` / `Str != Str` must continue to call `strcmp` directly on
    the two Str SSA values (loaded pointers), exactly as today - this path
    is untouched by the `_kai_str_concat` addressing fix (it is a totally
    separate call site: `params[0] = lv; params[1] = rv` are direct values,
    never address-of).
    """
    source = f"""fn main() -> Int {{
    let a = "{s1}"
    let b = "{s2}"
    if a == b {{
        print_int(1)
    }}
    return 0
}}
"""
    ir = compile_kai_source(source)

    call_match = re.search(r"call\s+i64\s+@strcmp\(([^)]*)\)", ir)
    assert call_match, f"Expected direct `call i64 @strcmp(...)` not found.\nIR:\n{ir}"

    args = call_match.group(1)
    # Exactly two pointer args, both direct SSA values (`ptr %s1, ptr %s2`
    # shaped), never an address-of a temporary/alloca-of-alloca pattern.
    assert re.match(r"^ptr\s+%\w+,\s*ptr\s+%\w+$", args.strip()), (
        f"strcmp call args shape regressed - expected two direct `ptr %x` "
        f"SSA values, got: {args!r}\nIR:\n{ir}"
    )
    # strcmp must be declared as taking 2 pointer params (unaffected by the
    # str_concat single-argument-array fix, which only touches strlen calls
    # inside _kai_str_concat).
    assert re.search(r"declare\s+i64\s+@strcmp\(ptr,\s*ptr\)", ir), (
        f"strcmp declaration shape regressed.\nIR:\n{ir}"
    )


@settings(max_examples=10, deadline=None, suppress_health_check=[HealthCheck.too_slow])
@given(n=st.integers(min_value=-100000, max_value=100000))
def test_preservation_print_int_uses_printf_directly(n):
    """
    **Validates: Requirements 3.13**

    `print_int` must continue to build a direct 2-element `[fmt, value]`
    argument array for `printf`, unaffected by the `_kai_str_concat` fix
    (which only touches the single-argument `strlen` call sites inside
    `emit_str_concat_helper`).
    """
    source = f"""fn main() -> Int {{
    print_int({n})
    return 0
}}
"""
    ir = compile_kai_source(source)
    assert re.search(
        r"call\s+i32\s+\(ptr,\s*\.\.\.\)\s+@printf\(ptr\s+@fmt_int,\s*i64\s+-?\d+\)",
        ir,
    ), f"print_int -> printf call shape regressed.\nIR:\n{ir}"


if __name__ == "__main__":
    import sys

    sys.exit(pytest.main([__file__, "-v"]))
