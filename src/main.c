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

bool opred(const char op_a, const char op_b);

int main(int argc, char** argv)
{
  Stack numstack = sk_init(&numstack);
  Stack opstack = sk_init(&opstack);
  Stack rpnstack = sk_init(&opstack);

  char* expr = "2+3*2";

  for (int i = 0; i < expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      sk_push(&rpnstack, expr[i]-'0');
      // sk_print(rpnstack);
    }
    else if (!isdigit(expr[i]) && expr[i] != ' ')
    {
      while (!sk_isempty(opstack) && opred(sk_peek(opstack), expr[i]))
      {
        sk_push(&rpnstack, sk_pop(&opstack));
      }
      sk_push(&opstack, expr[i]);
    }
  }
  while (!sk_isempty(opstack))
  {
    sk_push(&rpnstack, sk_pop(&opstack));
  }
  
  sk_print(rpnstack);
  sk_print(opstack);
  return 0;
}


/* Returns `true` if operator `op_a` precedence higher than `op_b`. */
bool opred(const char op_a, const char op_b)
{
  const struct Opred add = {.op = '+', .rank = 1};
  const struct Opred sub = {.op = '-', .rank = 1};
  const struct Opred mul = {.op = '*', .rank = 2};
  const struct Opred div = {.op = '/', .rank = 2};

  const struct Opred ops[] = {add, sub, mul, div};
  const int opslen = sizeof(ops) / sizeof(struct Opred);

  for (int i = 0; i < opslen; i++)
    if (ops[i].op == op_a)
      for (int j = 0; j < opslen; j++)
        if (ops[j].op == op_b)
          return ops[i].rank > ops[j].rank;
}