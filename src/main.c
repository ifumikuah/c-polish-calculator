/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include "stacklib.h"
#include "pnlib.h"

int main(int argc, char** argv)
{
  Stack newstack;
  newstack = sk_init(&newstack);

  int eval = pn_eval(&newstack, "3 5 5 5 / * + 2 2 ^ -");
  printf("%d \n", eval);

  return 0;
}