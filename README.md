# Reverse Polish (RPN) Calculator

Converts infix expression to postfix (RPN)

## User defined libraries

- Stack (array) implementation under `stacklib.h`.
- Evaluation related operation implementation under `pnlib.h`.

## Routines

### Stack

- Common stack operations are `push`, `pop`, `peek`, `isempty`, `size`.

### Evaluation related

- Parse numerical string into integer.
- Accepts inconsistenly spaced infix expression.
- Evaluate two operand based on operator.

## Future Plans

- Parse floating point string into double.
- Implement linked list for stack.
