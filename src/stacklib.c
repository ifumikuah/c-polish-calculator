/* RPN stack user-defined header definition */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

/* Print entire stack for debugging */
void sk_print(Stack sk)
{
  for (int i = 0; i < sk_size(sk); i++)
  {
    printf("%d ", sk.array[i]);
  }
  printf("\n");
}

/* Convert stack to string for debugging */
void sk_sprint(Stack sk)
{
  char n_str[sk_size(sk)+1];
  for (int i = 0; i < sk_size(sk); i++)
  {
    if (sk.array[i] > -1 && sk.array[i] < 10)
    {
      n_str[i] = sk.array[i]+'0';
    }
    else
    {
      n_str[i] = sk.array[i];
    }
  }
  n_str[sk_size(sk)] = '\0';

  printf("%s", n_str);
}

/* Initialize new string array */
SStack ss_init(SStack* ss_ptr)
{
  ss_ptr->cpos = -1;
  return *ss_ptr;
}

/* Push `str` to stack */
void ss_push(SStack* ss_ptr, char* str)
{
  --ss_ptr->cpos;
  strcpy(ss_ptr->array[ss_ptr->cpos], str);
}

/* Pop last in stack */
char* ss_pop(SStack* ss_ptr)
{
  if (ss_ptr->cpos < 0)
    return NULL;

  ss_ptr->cpos--;
  return ss_ptr->array[1+ss_ptr->cpos];
}

/* Read last item in stack */
char* ss_peek(SStack* ss)
{
  if (ss->cpos < 0)
    return NULL;
  
  return ss->array[ss->cpos];
}

/* Check if stack is empty */
bool ss_isempty(SStack ss)
{
  return ss.cpos < 0;
}