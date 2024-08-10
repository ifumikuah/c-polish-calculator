/* RPN stack user-defined header definition */

#include "stacklib.h"

/* Initialize new stack */
Stack sk_init(Stack* sk_ptr)
{
  sk_ptr->cpos = -1;

  for (int i = 0; i < MAXSTACK; i++)
    sk_ptr->array[i] = 0;

  return *sk_ptr;
}

/* Push `n_v` to stack */
int sk_push(Stack* sk_ptr, int n_v)
{
  if (sk_ptr->cpos > MAXSTACK-1)
    return sk_ptr->cpos;
  
  sk_ptr->cpos++;
  sk_ptr->array[sk_ptr->cpos] = n_v;

  return sk_ptr->cpos;
}

/* Pop last in stack */
int sk_pop(Stack* sk_ptr)
{
  if (sk_ptr->cpos < 0)
    return sk_ptr->cpos;
  
  sk_ptr->cpos--;

  return sk_ptr->array[1+sk_ptr->cpos];
}

/* Read last item in stack */
int sk_peek(Stack sk)
{
  if (sk.cpos < 0)
    return sk.cpos;
  
  return sk.array[sk.cpos];
}

/* Check if stack is empty */
bool sk_isempty(Stack sk)
{
  return sk.cpos < 0;
}

/* Check size of stack */
int sk_size(Stack sk)
{
  return sk.cpos+1;
}