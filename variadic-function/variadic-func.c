#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum drink { MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE };

double price(enum drink d) {
  switch (d) {
  case MUDSLIDE:
    return 6.79;
  case FUZZY_NAVEL:
    return 5.31;
  case MONKEY_GLAND:
    return 4.82;
  case ZOMBIE:
    return 5.89;
  }
  return 0;
}

/* You need a normal argument in a variadic function otherwise you will not be
 * able to tell the pre-compiler when the list of other arguments will start
 * (using the va_start macro) */
double total(int args, ...) {

  double total = 0;

  /* Symbolic "list" that holds all of the arguments passed in */
  va_list allArgs;

  /* We are saying that allArgs should contain the arguments
            passed into the function AFTER the "args" argument. */
  va_start(allArgs, args);

  for (int i = 0; i < args; i++) {

    enum drink d =
        va_arg(allArgs,
               enum drink); /* The arguments to this function are drink enums */

    total += price(d);
    printf("Current total: %lf\n", total);
  }

  va_end(allArgs); /* Telling the pre-compiler that no more arguments will be
                      passed into this function now!  */



  return total;
}

int main(int argc, char *argv[]) {

  printf("Price is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));

  return 0;
}
