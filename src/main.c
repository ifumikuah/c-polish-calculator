/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacklib.h"
#include "pnlib.h"

#define MAXLEN 100

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    printf("Usage: %s [expression]\n", argv[0]);
    printf("Example: %s 2+2+(3*2)\n", argv[0]);
    return 0;
  }

  char infix_buf[MAXLEN];
  for (int i = 1; i < argc; i++)
    strcat(infix_buf, argv[i]);
  
  char reformat_buf[MAXLEN];
  char* postfix_buf[MAXLEN] = {NULL};
  reformat(infix_buf, reformat_buf);
  infix_rpn(reformat_buf, postfix_buf);
  
  printf("%d\n", postfix_eval(postfix_buf));
  for (int i = 0; postfix_buf[i] != NULL; i++)
  {
    free(postfix_buf[i]);
  }
  
  return 0;
}