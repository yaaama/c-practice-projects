#include "calculator.h"
#include <stdbool.h>
#include <stdlib.h>







int main(int argc, char *argv[]) {



  /* Testing adding function */
  printf("Total: %f\n", add(5, (double) 1, 2.0, 3.0, 4.0, 5.0) );



  /* Stack push test... */
  printf("Creating new stack!\n");

  Stack *stack = malloc(sizeof(Stack));
  Datum data = {.operand = 20};
  stack_push(stack, data, OPERAND);
  Datum data2 = {.operand = 10};
  stack_push(stack, data2, OPERAND);
  Datum data3 = {.operand = 10};
  stack_pop(stack);

  Datum data4 = {.operand = 11};
  stack_push(stack, data4, OPERAND);
  stack_push(stack, data4, OPERAND);
  stack_push(stack, data4, OPERAND);
  print_stack(stack);

  stack_pop(stack);
  stack_pop(stack);
  stack_pop(stack);
  stack_pop(stack);


  print_stack(stack);
  stack_push(stack, data3, OPERAND);
  stack_push(stack, data4, OPERAND);

  print_stack(stack);





  return 0; }
