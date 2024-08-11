/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "stacklib.h"
#include "pnlib.h"

struct Opred
{
  char op;
  short rank;
};

int opred(const char op);
bool op_ge(const char op_a, const char op_b);
bool op_gt(const char op_a, const char op_b);

int main(int argc, char** argv)
{
  const char* expr = "6+5*3/5+8";

  Stack op = sk_init(&op);

  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      printf("%c", expr[i]);
    }
    else if (opred(expr[i]) != -1)
    {
      while (!sk_isempty(op) && op_ge(sk_peek(op), expr[i]))
      {
        printf("%c", sk_pop(&op));
      }
      sk_push(&op, expr[i]);
    }
    // printf(" ");
  }
  printf("%c", sk_pop(&op));
  
  return 0;
}


/* Returns `true` if operator `op_a` precedence greather than equal `op_b`. */
bool op_ge(const char op_a, const char op_b)
{
  if (opred(op_a) >= opred(op_b))
    return true;
  return false;
}

/* Returns `true` if operator `op_a` precedence greather than `op_b`. */
bool op_gt(const char op_a, const char op_b)
{
  if (opred(op_a) > opred(op_b))
    return true;
  return false;
}

/* Returns precedence of operator, greater the number higher the precedence */
int opred(const char c)
{
  if (c == '^')
    return 3;
  if (c == '/' || c == '*')
    return 2;
  if (c == '-' || c == '+')
    return 1;

  return -1;
}