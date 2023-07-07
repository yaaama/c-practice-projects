#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

/*  Stack data structure */

StackNode *stack_push(Stack *stack, char elem) {

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
    newNode->symbol = elem;
    /* newNode->type = elemType; */
    newNode->nextElem = NULL;
    stack->top = newNode;
    return newNode;
  }

  /* If stack was not empty... */
  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->symbol = elem;
  /* newNode->type = elemType; */
  stack->size += 1;

  /* Swap the current top node pointer to the new element being pushed on top */
  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  return newNode;
}

char stack_pop_c(Stack *stack) {

  StackNode *currTop = stack->top;

  StackNode *newTop = currTop->nextElem;

  if (currTop == NULL) {
    printf("Stack is empty already!\n");
    return 0;
  }

  char retChar = currTop->symbol;

  printf("Popping element -> %c\n ", currTop->symbol);

  /* The stack top pointer should point to the next element down */
  stack->top = newTop;

  /* Freeing the memory associated with the previous top */
  free(currTop);

  /* Decrementing size */
  stack->size -= 1;

  print_stack(stack);

  /* Returning the new top element in the stack */
  return retChar;
}

StackNode *stack_pop(Stack *stack) {

  /* New top of the stack will be the next element down */
  StackNode *currTop = stack->top;
  StackNode *newTop = currTop->nextElem;

  if (currTop == NULL) {
    printf("Stack is empty already!\n");
    return NULL;
  }

  printf("Popping element -> %c\n ", currTop->symbol);

  /* The stack top pointer should point to the next element down */
  stack->top = newTop;

  /* Freeing the memory associated with the previous top */
  free(currTop);

  /* Decrementing size */
  stack->size -= 1;

  print_stack(stack);

  /* Returning the new top element in the stack */
  return stack->top;
}

StackNode *stack_peek(Stack *stack) {

  if (stack->top == NULL) {
    printf("Stack is empty! Cannot peek.");
    return NULL;
  }

  return stack->top;
}

bool stack_is_empty(Stack *stack) {

  if (stack->top == NULL) {
    return true;
  }

  return false;
}

int stack_size(Stack *stack) {

  if ((stack == NULL) || (stack->top == NULL)) {
    return 0;
  }

  return stack->size;
}

void print_stack(Stack *stack) {

  StackNode *node = stack->top;
  StackNode *temp = NULL;

  printf("Top -> ");

  while (node != NULL) {

    printf("%c -> ", (char)node->symbol);

    node = node->nextElem;
  }

  printf("\n");
}

int precedence(char operator) {

  switch (operator) {
  case '*':
    return 1;
  case '/':
    return 1;
  case '-':
    return 0;
  case '+':
    return 0;
  case '(':
    return 0;
  case ')':
    return 2;
  default:
    return -1;
  }
}

bool is_operator(char c) {

  switch (c) {
  case '+':
  case '*':
  case '/':
  case '-':
  case '(':
  case ')':
    printf("%c it is an operator\n", c);
    return true;
  }

  return false;
}

/* Function that parses the expression given,
   collects result in POSTFIX notation
   MALLOC's */
char *convert_to_postfix(char *expr, int size) {

  char *postfix =
      malloc(sizeof(char) * (size + 1)); /* size+1 used for null char */

  Stack *stack = malloc(sizeof(Stack));

  /* Precedence is -1 because stack is empty! */
  int stackPrec = -1;

  int c = 0;

  for (int i = 0; i < size; i++) {

    char currentChar = expr[i];
    int currentPrec = precedence(currentChar);

    if (!is_operator(currentChar)) {
      postfix[c] = currentChar;
      printf("Appending %c to postfix[%d]\n", (char)currentChar, c);
      c += 1;
    } else {
      if (currentPrec > stackPrec) {
        printf("%c is higher than whatever is on the stack\n", currentChar);
        stack_push(stack, currentChar);
        printf("Pushing symbol: %c\n", (char)currentChar);
      }
    }
  }

  print_stack(stack);

  const int finalStackSize = stack->size;
  for (int i = 0; i < finalStackSize; i++) {
    char app = stack_pop_c(stack);
    printf("Popped %c from the stack\n", app);
    postfix[c + i] = app;
    printf("Appending %c to postfix[%d]\n", (char)app, c);
  }

  print_stack(stack);

  /* Freeing up the memory for the stack */
  if (destroy_stack(stack) == 0) {
    printf("Stack could not be destroyed, system exiting...");
    exit(1);
  }

  /* Placing null terminator at the end */
  postfix[size + 1] = '\0';

  printf("Here is the final string:\n");
  print_string(postfix, size);



  return postfix;
}


int destroy_stack(Stack *stack) {

  if (stack == NULL) {

    printf("Stack is NULL! Cannot destroy, returning error...\n");
    return 0;
  }

  free(stack);

  return 1;
}

/***********************/
/* /\* Extra stuff *\/ */
/***********************/

void print_string(char *str, int size) {

  for (int i = 0; i < size; i ++) {
    printf("%c", str[i]);
  }

  printf("\n");
}

double operate(int k, char *expr) {

  double total = 0;

  return total;
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
