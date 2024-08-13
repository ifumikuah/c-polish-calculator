/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "stacklib.h"
#include "pnlib.h"

int main(int argc, char** argv)
{
  const char* expr = "7+5* 33 /5^1+(3-2)";
  char expr_buf[100];
  char* infix_buf[20] = {NULL};

  Stack op = sk_init(&op);
  reformat(expr, expr_buf);

  infix_rpn(expr_buf, infix_buf);
  for (int i = 0; infix_buf[i] != NULL; i++)
  {
    printf("%s ", infix_buf[i]);
  }
  
  // printf("%s", expr_buf);
  return 0;
}