---
name: agent
description: Agent workflow for editing Kai code with compiler feedback.
---

# Kai Agent Workflow

Use this when editing Kai code. Kai is a compiled systems language that
transpiles to C. Use the compiler feedback loop to find and fix errors.

## Edit Loop

1. Edit the .kai source file.
2. Run `kai check <file>` to type-check without generating output.
3. Read the diagnostics and fix the errors.
4. Repeat until clean.

For structured debugging, use JSON output:

```sh
kai check --json <file>
kai explain E0001
```

## Diagnostic Format

Text output:
```
error[E0001]: type mismatch in declaration of 'x': expected 'Int', got 'Str'
```

JSON output (`--json`) adds structured fields including code, message, and file.

## Commands

- `kai check <file>` — type-check only
- `kai check --json <file>` — type-check with JSON diagnostics
- `kai explain <code>` — explain an error code
- `kai skills` — list available skills
- `kai skills get <topic>` — load a skill by name

## Fix Safety Guidelines

When fixing diagnostics:
- Start with the first reported error — later errors may be cascading.
- Read the `explain` output for the error code to understand the root cause.
- Apply the fix described in the error message.
- Re-check after each fix.
