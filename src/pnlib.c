/* RPN evaluation related header definition */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacklib.h"
#include "pnlib.h"

/* Evaluate binary expression */
int bin_eval(int n1, int n2, char op)
{
  switch (op)
  {
  case '-':
    return n2 - n1;
  case '+':
    return n2 + n1;
  case '*':
    return n2 * n1;
  case '/':
    return n2 / n1;
  case '%':
    return n2 % n1;
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

/* Evaluate `expr` string with space delimiter as RPN expression */
int pn_eval_(Stack *sk_ptr, const char *expr)
{
  Stack tmp_num;
  tmp_num = sk_init(&tmp_num);

  /* initialize place value counter for digits */
  int exp = 0;
  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isdigit(expr[i]))
    {
      /* pushing each digit into temporary value stack before parsing digits */
      sk_push(&tmp_num, expr[i] - '0');
      /* each digits increments the place value */
      exp++;
    }
    else if (expr[i] == ' ' || opred(expr[i]) != -1) /* if space  encountered, we'll start parsing digits in `tmp_num` stack */
    {
      int dec = 1; /* with rightmost digit as top of stack, starts with 10^0 */
      int sum = 0;

      /* this will pop and sum the stack exponentially by ten until it reaches empty stack */
      while (exp--)
      {
        sum += sk_pop(&tmp_num) * dec; /* review 'how decimal works' in order to understand this routine */
        dec *= 10;
      }
      exp = 0; /* resets the place value counter */

      /* pushes `tmp_num` parsed integer into real stack as operand */
      sk_push(sk_ptr, sum);
    }
    if (expr[i] != ' ' && !isdigit(expr[i])) /* starts evaluate in the real stack if encounters operator charr */
    {
      sk_push(sk_ptr, bin_eval(sk_pop(sk_ptr), sk_pop(sk_ptr), expr[i]));
    }
  }

  return sk_pop(sk_ptr);
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