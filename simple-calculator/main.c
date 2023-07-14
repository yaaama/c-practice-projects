#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "calculator.h"






int main(int argc, char *argv[]) {
  /* Testing adding function */
  /* printf("Total: %f\n", add(5, (double) 1, 2.0, 3.0, 4.0, 5.0) ); */
  /* Stack push test... */
  printf("Creating new stack!\n");
  Stack *stack = malloc(sizeof(Stack));

  /* char symbols[] = "+-/"; */

  /* Datum data[3]; */
  /* Datum symb[3]; */

  /* for (int i = 0; i < 3; i++ ) { */
  /*   data[i].operand = (i + 4); */
  /*   symb[i].op = symbols[i]; */

  /* } */

  /* for (int i = 0; i < 3 ; i ++ ) { */

  /* stack_push(stack, data[i].operand, OPERAND); */
  /* stack_push(stack, symb[i]., OPERATOR); */
  /* } */

  /* printf("Stack size: %d \n", stack_size(stack) ); */
  /* printf("Stack empty?: %d \n", stack_is_empty(stack) ); */

  /* destroy_stack(stack); */




  char expr[] = "10 + 20 * 30 - 40 / 50";

  convert_to_postfix(expr, strlen(expr) + 1);

  /* /\* convert_to_postfix(expr, strlen(expr)); *\/ */

  /* char str[] = "20.30300 + 2.444"; */
  /*  char *ptr; */
  /*  double ret; */

  /*  ret = strtod(str, &ptr); */
  /*  double second = strtod(ptr+2, &ptr ); */
  /*  printf("The number(double) is %lf\n", ret); */
  /*  printf("String part is |%s|\n", ptr); */
  /*  printf("Second part is %lf\n", second); */






  return 0;
}
