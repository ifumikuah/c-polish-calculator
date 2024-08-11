#ifndef STACKLIB_H
#define STACKLIB_H

#include <stdbool.h>

#define MAXSTACK 24

typedef struct Stack
{
  int array[MAXSTACK];
  int cpos;
} Stack;

Stack sk_init(Stack* sk_ptr);
int sk_push(Stack* sk_ptr, int n_v);
int sk_pop(Stack* sk_ptr);
int sk_peek(Stack sk);
bool sk_isempty(Stack sk);
int sk_size(Stack sk);
void sk_print(Stack sk);

#endif