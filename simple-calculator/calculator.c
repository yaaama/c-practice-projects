#include "calculator.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*  Stack data structure */


StackNode *stack_push(Stack *stack, Datum newElem, ELEMENT_TYPE elemType) {

/* Checking if the stack is null (no elements) */
  if (stack->top == NULL) {

    /* Create a new node*/
    StackNode *newNode = malloc(sizeof(StackNode));

    /* If malloc fails then exit system */
    if (newNode == NULL) {
      printf("Serious error! Malloc failed for new stack node.\n");
      exit(1);
    }

    /* If we were given an empty stack then we should set the size to 1 now */
    stack->size = 1;
    newNode->data = newElem;
    newNode->type = elemType;
    newNode->nextElem = NULL;
    stack->top = newNode;
    return newNode;
  }

  /* If stack was not empty... */
  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->data = newElem;
  newNode->type = elemType;
  stack->size += 1;

  /* Swap the current top node pointer to the new element being pushed on top */
  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  return newNode;
}



StackNode *stack_pop(Stack *stack) {

  /* New top of the stack will be the next element down */
  StackNode *currTop = stack->top;
  StackNode *newTop = currTop->nextElem;

  if (currTop == NULL) {
    printf("Stack is empty already!\n");
    return NULL;
  }

  /* The stack top pointer should point to the next element down */
  stack->top = newTop;

  /* Freeing the memory associated with the previous top */
  free(currTop);

  /* Returning the new top element in the stack */
  return stack->top;
}


void print_stack(Stack *stack) {

  StackNode *node = stack->top;
  StackNode *temp = NULL;

  printf("Top -> ");


  while (node != NULL) {

    printf("%d -> " , node->data.operand);

    node = node->nextElem;

      }

    printf("\n");

}
















/*  So we will have an expression such as: ((2 * 4 * 6)/ 3) + 100
   We want to then parse the expression into its simple parts and
  work on them individually and return an answer. */
/*  Inner most bracket has to be done done first */

/* Will add k number of arguments together */
double add(int k, ...) {

  double total = 0;

  va_list argList;
  va_start(argList, k);

  for (int i = 0; i < k; i++) {

    double operand = va_arg(argList, double);
    total += operand;
    printf("Current total: %lf\n", total);
  }

  va_end(argList);

  return total;
}




double operate(int k, char *expr) {

  double total = 0;

  return total;
}
