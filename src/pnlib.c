/* RPN evaluation related header definition */

#include <ctype.h>
#include <stdio.h>

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

/* Evaluate `expr` string with space delimiter as RPN expression */
int pn_eval(Stack* sk_ptr, const char* expr)
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
      sk_push(&tmp_num, expr[i]-'0');
      /* each digits increments the place value */
      exp++;
    } 
    else if (expr[i] == ' ') /* if space  encountered, we'll start parsing digits in `tmp_num` stack */
    {
      if (!isdigit(expr[i-1])) /* skips this parsing operation steps if we just finish an evaluation*/
        continue;

      int dec = 1; /* with rightmost digit as top of stack, starts with 10^0 */
      int sum = 0;

      /* this will pop and sum the stack exponentially by ten until it reaches empty stack */
      while (exp--)
      {
        sum += sk_pop(&tmp_num)*dec; /* review 'how decimal works' in order to understand this routine */
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