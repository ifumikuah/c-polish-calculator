# Reverse Polish (RPN) Calculator

Evaluate reverse polish notation in string.

Space as expression delimiters.

## User defined libraries

- Stack (array) implementation under `stacklib.h`.
- Evaluation related operation implementation under `pnlib.h`.

## Routines

### Stack

- Common stack operations are `push`, `pop`, `peek`, `isempty`, `size`.

### Evaluation related

- Parse numerical string into integer.
- Evaluate two operand based on operator.

## Future Plans

- Parse floating point string into double.
- Parse infix expression into RPN.
- Implement linked list for stack.