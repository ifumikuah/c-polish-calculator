#ifndef STACKLIB_H
#define STACKLIB_H

#include <stdbool.h>

#define MAXSTACK 50
#define MAXROW 10

typedef struct Stack
{
  int array[MAXSTACK];
  int cpos;
} Stack;
typedef struct SStack
{
  char array[MAXSTACK][MAXROW];
  int cpos;
} SStack;

Stack sk_init(Stack* sk_ptr);
int sk_push(Stack* sk_ptr, int n_v);
int sk_pop(Stack* sk_ptr);
int sk_peek(Stack sk);
bool sk_isempty(Stack sk);
int sk_size(Stack sk);
void sk_print(Stack sk);
void sk_sprint(Stack sk);

SStack ss_init(SStack* sk_ptr);
void ss_push(SStack* sk_ptr, char* str);
char* ss_pop(SStack* sk_ptr);
char* ss_peek(SStack* ss);
bool ss_isempty(SStack sk);

#endif