/* RPN evaluation related header definition */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacklib.h"
#include "pnlib.h"

/* Evaluate postfix expression */
long postfix_eval(char* postfix[])
{
  Stack num = sk_init(&num);

  for (int i = 0; postfix[i] != NULL; i++)
  {
    if (is_str_numeral(postfix[i]))
    {
      sk_push(&num, atol(postfix[i]));
    }
    else
    {
      int eval = bin_eval(sk_pop(&num), sk_pop(&num), postfix[i][0]);
      sk_push(&num, eval);
    }
  }
  return sk_pop(&num);
}

/* Evaluate binary expression */
int bin_eval(int n1, int n2, char op)
{
  switch (op)
  {
  case '-':
    return n1 - n2;
  case '+':
    return n1 + n2;
  case '*':
    return n1 * n2;
  case '/':
    return n1 / n2;
  case '%':
    return n1 % n2;
  case '^':
    int sum = 1;
    for (int i = 0; i != n2; i++)
      sum *= n1;
    return sum;

  default:
    return 0;
  }
}

/* Parse Infix expression to RPN */
void infix_rpn(const char* expr, char* rpn_expr[])
{
  Stack opstack = sk_init(&opstack);

  char opr_tmp[2];
  char digit_tmp[8];

  int d_i = 0;
  int j = 0;

  for (int i = 0; expr[i] != '\0'; i++)
  {
    char c = expr[i];
    if (c == ' ' && isdigit(expr[i-1]))
    {
      digit_tmp[d_i] = '\0';
      d_i++;
      rpn_expr[j] = malloc(sizeof(char)*d_i);
      strcpy(rpn_expr[j], digit_tmp);
      j++;
      d_i = 0;
    }
    else if (isdigit(c))
    {
      digit_tmp[d_i] = c;
      d_i++;
    }
    else if (c == '(')
    {
      sk_push(&opstack, c);
    }
    else if (c == ')')
    {
      while (!sk_isempty(opstack) && sk_peek(opstack) != '(')
      {
        c_to_str(sk_pop(&opstack), opr_tmp);
        rpn_expr[j] = malloc(sizeof(char)*2);
        strcpy(rpn_expr[j], opr_tmp);
        j++;
      }
      sk_pop(&opstack);
    }
    else if (opred(c) != -1)
    {
      while (!sk_isempty(opstack) && opred(sk_peek(opstack)) >= opred(c))
      {
        c_to_str(sk_pop(&opstack), opr_tmp);
        rpn_expr[j] = malloc(sizeof(char)*2);
        strcpy(rpn_expr[j], opr_tmp);
        j++;
      }
      sk_push(&opstack, c);
    }
  }
  while (!sk_isempty(opstack))
  {
    c_to_str(sk_pop(&opstack), opr_tmp);
    rpn_expr[j] = malloc(sizeof(char)*2);
    strcpy(rpn_expr[j], opr_tmp);
    j++;
  }
}

/* Evaluate string RPN expression */
int pn_eval(const char *expr)
{
  Stack digit_s = sk_init(&digit_s);
  Stack op_s = sk_init(&op_s);
  Stack main_s = sk_init(&main_s);

  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      sk_push(&digit_s, expr[i] - '0');
    }
    else if (!isdigit(expr[i]) && opred(expr[i]) == -1)
    {
      int dec = 1;
      int sum = 0;

      while (!sk_isempty(digit_s))
      {
        sum += sk_pop(&digit_s) * dec;
        dec *= 10;
      }
      sk_push(&main_s, sum);
    }
    else if (opred(expr[i]) != -1)
    {
      int eval = bin_eval(sk_pop(&main_s), sk_pop(&main_s), expr[i]);
      sk_push(&main_s, eval);
    }
  }

  sk_print(main_s);
}

/* Reformat inconsistenly formated user input */
void reformat(const char* expr, char* buf)
{
  int j = 0;
  for (int i = 0; expr[i] != '\0'; i++)
  {
    char c = expr[i];
    if (c == ' ')
      continue;
    
    if (isdigit(c))
    {
      buf[j++] = c;
    }
    else if (!isdigit(c))
    {
      if (c != '(')
        buf[j++] = ' ';

      buf[j++] = c;

      if (c != ')')
        buf[j++] = ' ';
    }
  }
  if (isdigit(buf[j-1]))
    buf[j++] = ' ';

  buf[j] = '\0';
}

/* Operator precedence */
int opred(const char c)
{
  switch (c)
  {
  case '^':
    return 3;
  case '/':
  case '*':
    return 2;
  case '-':
  case '+':
    return 1;
  default:
    return -1;
  }
}

/* Operand to char, convert operand char to string */
void c_to_str(const char c, char* buf)
{
  buf[0] = c;
  buf[1] = '\0';
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

/* Return `true` if all char in string contains numeral */
bool is_str_numeral(const char* str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i]))
      return false;
  }
  return true;
}