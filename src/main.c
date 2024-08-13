/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "stacklib.h"
#include "pnlib.h"

int main(int argc, char** argv)
{
  const char* expr = "(7+(3+2))*3";
  char expr_buf[100];
  char* postfix_buf[20] = {NULL};

  Stack op = sk_init(&op);
  reformat(expr, expr_buf);
  infix_rpn(expr_buf, postfix_buf);
  
  printf("%d\n", postfix_eval(postfix_buf));
  return 0;
}