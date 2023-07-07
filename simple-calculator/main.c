#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "calculator.h"






int main(int argc, char *argv[]) {
  /* Testing adding function */
  /* printf("Total: %f\n", add(5, (double) 1, 2.0, 3.0, 4.0, 5.0) ); */
  /* Stack push test... */
  printf("Creating new stack!\n");
  /* Stack *stack = malloc(sizeof(Stack)); */
  /* stack_push(stack, '*'); */
  /* stack_push(stack, '1'); */
  /* stack_pop(stack); */
  /* stack_push(stack, 'x'); */
  /* stack_push(stack, 'x'); */
  /* stack_push(stack, 'x'); */
  /* print_stack(stack); */
  /* stack_pop(stack); */
  /* stack_pop(stack); */
  /* stack_pop(stack); */
  /* stack_pop(stack); */
  /* print_stack(stack); */
  /* stack_push(stack, 3 ); */
  /* stack_push(stack, 4); */
  /* print_stack(stack); */



  char *expr = "(A+B)+(C*D)+E";

  char *newExpr = convert_to_postfix(expr, 13);






  return 0;
}
