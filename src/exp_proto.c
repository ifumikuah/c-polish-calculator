/* Base idea/model for infix-postfix implementation */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "stacklib.h"
#include "pnlib.h"

#define MAXBUF 100

void print_inpost(Stack* sk, const char* expr);
void parse_dig(const char* expr);
bool op_ge(const char op_a, const char op_b);
bool op_gt(const char op_a, const char op_b);
void intopr(const char* expr, char* buf);

int main(int argc, char** argv)
{
  const char* expr = "8*(5^4+2)-6^2/(9*3)";
  const char* expr2 = "9 2 {43}{35} 2";
  Stack pr = sk_init(&pr);
  Stack stc = sk_init(&stc);

  char exp_buf[MAXBUF];
  intopr("68 + 90 - (4 * 5)", exp_buf);

  pn_eval("68 90 + 5 -");

  return 0;
}

/* Generate postfix string from infix expression */
void intopr(const char* expr, char* buf)
{
  Stack stack = sk_init(&stack);

  int j = 0;
  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      buf[j++] = expr[i];
    }
    else if (expr[i] == '(')
    {
      sk_push(&stack, expr[i]);
    }
    else if (expr[i] == ')')
    {
      while (!sk_isempty(stack) && sk_peek(stack) != '(')
      {
        buf[j++] = sk_pop(&stack);
      }
      sk_pop(&stack);
    }
    else if (opred(expr[i]) != -1)
    {
      buf[j++] = ' ';
      while (!sk_isempty(stack) && op_ge(sk_peek(stack), expr[i]))
      {
        buf[j++] = sk_pop(&stack);
      }
      sk_push(&stack, expr[i]);
    }
  }
  while (!sk_isempty(stack))
  {
    buf[j++] = sk_pop(&stack);
  }
  buf[j] = '\0';
}

/* Parse and print multidigit number wrapped by curly braces */
void parse_dig(const char* expr)
{
  Stack ns = sk_init(&ns); // stack for digit
  Stack pr = sk_init(&pr); // stack for brackets

  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      /* If digit are member of bracket pair, push to digit stack */
      if (sk_peek(pr) == '{')
      {
        sk_push(&ns, expr[i]-'0');
      }
      /* Else, just print the number */
      else
      {
        printf("%d ", expr[i]-'0');
      }
    }
    /* If opening bracket encountered, push to bracket stack, trigger the digit parsing for future digit occurenxe */
    else if (expr[i] == '{')
    {
      sk_push(&pr, expr[i]);
    }
    /* If closing bracket encountered, we'll start parsing digits in stack correspond to it's place value in decimal */
    else if (expr[i] == '}')
    {
      int intv = 1;
      /* The final product stored into `sum` */
      int sum = 0;

      /* Refer to 'how decimal works' for understand this loop */
      while (!sk_isempty(ns))
      {
        sum += sk_pop(&ns) * intv;
        intv *= 10;
      }
      /* Pop and discard the bracket pair, ending a multidigit parse sequence */
      sk_pop(&pr);

      /* Print the parsed integer product stored in `sum` */
      printf("%d ", sum);
    }
  }
}

/* Evaluate infix expression to postfix (experimental) */
void print_inpost(Stack* sk, const char* expr)
{
  for (int i = 0; expr[i] != '\0'; i++)
  {
    /* If `expr` is digit, print to console */
    if (isdigit(expr[i]))
    {
      printf("%c", expr[i]);
    }
    /* If `expr` is opening bracket, always push to stack once */
    else if (expr[i] == '(')
    {
      sk_push(sk, expr[i]);
    }
    /* If `expr` is closing bracket, pop and print to console, operators until `(` was top of stack */
    else if (expr[i] == ')')
    {
      while (!sk_isempty(*sk) && sk_peek(*sk) != '(')
      {
        printf("%c", sk_pop(sk));
      }
      /* And discard that `(` opening bracket */
      sk_pop(sk);
    }
    /* If `expr` is operator */
    else if (opred(expr[i]) != -1)
    {
      /* If stack doesn't empty and top stack operator precedence higher than equal `expr`, pop and print to the console */
      while (!sk_isempty(*sk) && op_ge(sk_peek(*sk), expr[i]))
      {
        printf("%c", sk_pop(sk));
      }
      /* Push that `expr` to the stack anyway */
      sk_push(sk, expr[i]);
    }
  }
  /* Pop and print the rest operators */
  while (!sk_isempty(*sk))
  {
    printf("%c", sk_pop(sk));
  }
  printf("\n");
}

/* Returns `true` if operator `op_a` precedence greather than equal `op_b`. */
bool op_ge(const char op_a, const char op_b)
{
  return opred(op_a) >= opred(op_b);
}

/* Returns `true` if operator `op_a` precedence greather than `op_b`. */
bool op_gt(const char op_a, const char op_b)
{
  return opred(op_a) > opred(op_b);
}