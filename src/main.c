/* Reverse Polish (RPN) calculator - main*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "stacklib.h"
#include "pnlib.h"

int main(int argc, char** argv)
{
  const char* expr = "7+5*3/5^1+(3-2)";

  Stack op = sk_init(&op);

  return 0;
}