#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculator.h"

/* Numb of elements allowed in a single stack */
#define STACK_LIM 100
/* Number of digits allowed in a numb */
#define DIGIT_LIM 10

/*  Stack data structure */

void push_character(Stack *stack, char datum) {

  Datum data = {.op = datum};

  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->type = OPERATOR;
  newNode->symbol = data;

  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  printf("Pushed char %c to stack.\n", (char) stack->top->symbol.op);
}

 void push_number(Stack *stack, int datum) {

  Datum data = {.operand = datum};

  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->type = OPERAND;
  newNode->symbol = data;

  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  printf("Pushed integer %d to stack.\n", (int) stack->top->symbol.operand);
}

StackNode *stack_push(Stack *stack, void *datum, ELEMENT_TYPE type) {


  if (stack->top == NULL || stack_is_empty(stack)) {
  }

  if (stack->size == STACK_LIM) {
    printf("Stack size is full! Exiting.");
    exit(0);
  }

  switch (type) {
  case OPERAND: {
    push_number(stack, *(int *) datum);
    stack->size += 1;
  } break;

  case OPERATOR: {
    push_character(stack, *(char *)datum);
    stack->size += 1;
  } break;
  }

  print_stack(stack);

  return stack->top;
}

/* If the stack is not empty */

StackNode *stack_pop(Stack *stack) {

  /* New top of the stack will be the next element down */
  StackNode *currTop = stack->top;
  StackNode *newTop = currTop->nextElem;

  if (currTop == NULL) {
    printf("Stack is empty already!\n");
    return NULL;
  }

  if (currTop->type == OPERATOR) {
    printf("Pop -> %c\n", currTop->symbol.op);
  } else {
    printf("Pop -> %d\n", currTop->symbol.operand);
  }

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

  if (stack->top == NULL || stack->size == 0) {
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

  printf("Stack:\tTop -> ");

  while (node != NULL) {

    if (node->type == OPERATOR) {
      printf("%c -> ", (char) node->symbol.op);
    } else {
      printf("%d -> ", (int) node->symbol.operand);
    }

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

bool is_digit(char c) {

  switch (c) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    printf("%c is a digit.\n", c);
    return true;
  }

  return false;
}

void strip_string_whitespace(char *restrict untrimmedStr,
                             char *restrict trimmedStr) {

  printf("Trimmed string: \n");
  while (*untrimmedStr != '\0') {

    if (!isspace(*untrimmedStr)) {
      *trimmedStr = *untrimmedStr;
      printf("%c", *trimmedStr);
      trimmedStr++;
    }

    untrimmedStr++;
  }

  printf("\n");
  *trimmedStr = '\0';
}

Stack *convert_to_postfix(char *expr, int length) {

  Stack *postfixStack = malloc(sizeof(Stack));
  postfixStack->size = 0;

  char *strippedExpr = malloc(sizeof(length));
  strip_string_whitespace(expr, strippedExpr);

  return postfixStack;
}

/* Function that parses the expression given,
   collects result in POSTFIX notation
   MALLOC's */
/* char *convert_to_postfix(char *expr, int size) { */

/*     char *postfix = */
/*         malloc(sizeof(char) * (size + 1)); /\* size+1 used for null char *\/
 */

/*     char **post_expr = malloc((sizeof(char) * (size + 1)) * 10); /\* string
 * array *\/ */

/*     Stack *stack = malloc(sizeof(Stack)); */

/*     /\* Precedence is -1 because stack is empty! *\/ */
/*     int stackPrec = -1; */

/*     int c = 0; */

/*     for (int i = 0; i < size; i++) { */

/*         char currentChar = expr[i]; */

/*         /\* Skip whitespace *\/ */
/*         if (currentChar == ' ') { */
/*             continue; */
/*         } */

/*         int currentPrec = precedence(currentChar); */

/*         if (!is_operator(currentChar)) { /\* If element is a digit *\/ */

/*             postfix[c] = currentChar; */
/*             printf("Appending %c to postfix[%d]\n", (char)currentChar, c); */
/*             c += 1; */

/*         } else {                    /\* If element is an operand *\/ */
/*             if (currentPrec > stackPrec) { */
/*                 printf("%c is higher than whatever is on the stack\n",
 * currentChar); */
/*                 stack_push(stack, currentChar); */
/*                 printf("Pushing symbol: %c\n", (char)currentChar); */
/*             } */
/*         } */
/*     } */

/*     print_stack(stack); */

/*     const int finalStackSize = stack->size; */
/*     for (int i = 0; i < finalStackSize; i++) { */
/*         char app = stack_pop_c(stack); */
/*         printf("Popped %c from the stack\n", app); */
/*         postfix[c + i] = app; */
/*         printf("Appending %c to postfix[%d]\n", (char)app, c); */
/*     } */

/*     print_stack(stack); */

/*     /\* Freeing up the memory for the stack *\/ */
/*     if (destroy_stack(stack) == 0) { */
/*         printf("Stack could not be destroyed, system exiting..."); */
/*         exit(1); */
/*     } */

/*     /\* Placing null terminator at the end *\/ */
/*     postfix[size + 1] = '\0'; */

/*     printf("Here is the final string:\n"); */
/*     print_string(postfix, size); */

/*     return postfix; */
/* } */

int destroy_stack(Stack *stack) {

  printf("Destroying stack!\n");
  if (stack == NULL) {

    printf("Stack is NULL! Cannot destroy, returning error...\n");
    return 0;
  }

  while (stack->top != NULL) {
    stack_pop(stack);
  }

  free(stack);


  return 1;
}

/***********************/
/* /\* Extra stuff *\/ */
/***********************/

void print_string(char *str, int size) {

  for (int i = 0; i < size; i++) {
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
