---
name: diagnostics
description: Read Kai diagnostics, explanations, and fix guidance.
---

# Kai Diagnostics

Kai diagnostics are structured error messages designed for both
humans and AI agents. Each diagnostic has a unique code, a descriptive
message, and a suggested fix.

## Commands

```
kai check <file>
kai explain <code>
kai check --json <file>
```

## Diagnostic Format

Text:
```
error[E0001]: type mismatch in declaration of 'a': expected 'Int', got 'Str'
```

## Error Codes

| Code | Description |
|------|-------------|
| E0001 | Type mismatch in variable declaration |
| E0002 | Type mismatch in assignment |
| E0003 | Argument type mismatch |
| E0004 | Field type mismatch in struct initializer |
| E0005 | Argument count mismatch in function call |
| E0006 | Argument count mismatch in method call |
| E0007 | Return type mismatch |
| E0008 | Cannot assign to immutable variable |
| E0009 | Use of moved value |
| E0010 | Cannot return reference to local variable |
| E0011 | Field access on optional type |
| E0012 | Method call on optional type |
| E0013 | Field does not exist in struct |
| E0014 | Cannot use 'try' on non-error-union type |
| E0015 | Cannot use 'try' in non-error-returning function |
| E0016 | Error set mismatch in 'try' |
| E0017 | Cannot use 'catch' on non-optional/non-error-union type |
| E0018 | Catch fallback type mismatch |
| E0019 | Undefined identifier |
| E0020 | Undefined function |
| E0021 | Undefined struct |
| E0022 | Undefined method |
| E0100 | Lexer error |
| E0101 | Parser error |

## Agent Triage

1. Read the error message and code.
2. Run `kai explain <code>` for detailed guidance.
3. Fix the first error first.
4. Re-check after each fix.
