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

  printf("Pushed char %c to stack.\n", stack->top->symbol.op);
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

  printf("Pushed integer %d to stack.\n", (int)stack->top->symbol.operand);
}

StackNode *stack_push(Stack *stack, Datum datum, ELEMENT_TYPE type) {

  if (stack->top == NULL || stack_is_empty(stack)) {
    printf("Stack is empty!\n");
  }

  if (stack->size == STACK_LIM) {
    printf("Stack size is full! Exiting.");
    exit(0);
  }

  Datum temp;
  switch (type) {
  case OPERAND: {
    push_number(stack, datum.operand);
    stack->size += 1;
  } break;

  case OPERATOR: {
    push_character(stack, datum.op);
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

void expr_remove_whitespace(char *restrict untrimmedStr,
                            char *restrict trimmedStr) {

  printf("Removing whitespace: \n");
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

void expr_remove_parens(char *restrict untrimmedStr,
                        char *restrict trimmedStr) {

  printf("Removing parentheses: \n");
  int count = 0;
  while (*untrimmedStr != '\0') {

    if (*untrimmedStr != '(' && *untrimmedStr != ')') {
      *trimmedStr = *untrimmedStr;
      printf("%c", *trimmedStr);
      count++;
      trimmedStr++;
    }

    untrimmedStr++;
  }

  printf("\n");
  *trimmedStr = '\0';
}

void free_string_mem(char *str, int length) {

  for (int i = 0; i < length; i++) {
    free(str);
    str++;
  }
}

int postfix_evaluate(Stack *expr) { return 0; }

/* Converts given string into a postfix expression */
Stack *convert_to_postfix(char *expr, int length) {

  char *wsRemoved = malloc(sizeof(char) * (length + 1));
  expr_remove_whitespace(expr, wsRemoved); /* Removes the whitespace */
  char *cleanExpr = malloc(sizeof(char) * (length + 1));
  expr_remove_parens(wsRemoved, cleanExpr);

  size_t leng = strlen(cleanExpr);
  leng += 1; /* Accounts for the null terminator */
  printf("Original length: %d , trimmed length: %zu\n", length, leng);

  Stack *postfixStack = malloc(sizeof(Stack));
  postfixStack->size = 0;
  postfixStack->top = NULL;
  Stack *tempStack = malloc(sizeof(Stack));
  tempStack->size = 0;
  tempStack->top = NULL;

  int currentNumber;
  char currentChar;
  int place = 0;

  for (size_t i = 0; i < leng; i++) {

    currentNumber = 0;
    currentChar = cleanExpr[i];

    if(currentChar == '\0') {
      break;
    }

    if (isdigit(currentChar)) {

      while (isdigit(currentChar) && i < leng) {
        currentNumber = (int)currentNumber * 10 + (currentChar - '0');
        i++;
        currentChar = cleanExpr[i];
      }

      Datum temp = {.operand = currentNumber};
      stack_push(postfixStack, temp, OPERAND);
      i--;


                                /* When the scanned character is an operator */
    } else if (is_operator(currentChar)) {

      if (tempStack->top == NULL) {
        Datum temp = {.op = currentChar};
        stack_push(tempStack, temp, OPERATOR);
        continue;
      }

      // Pop from stack to the output while top of stack has the same or greater
      // precedence
      int tempTopPrec = precedence(stack_peek(tempStack)->symbol.op);
      int charPrec = precedence(currentChar);

      if (charPrec <= tempTopPrec) {

        Datum temp = stack_peek(tempStack)->symbol;
        Datum nextDatum = {.op = currentChar};
        /* Pop op stack that has either the same or higher precedence than the current op (charPrec) */
        while(charPrec <= tempTopPrec && !stack_is_empty(tempStack)) {

        stack_push(postfixStack, temp, OPERATOR);

        stack_pop(tempStack);

        if(stack_peek(tempStack) != NULL) {
        tempTopPrec = precedence(stack_peek(tempStack) ->symbol.op);
        temp = stack_peek(tempStack)->symbol;
        }


        }
        stack_push(tempStack, nextDatum, OPERATOR);
      } else {
        Datum temp = {.op = currentChar};
        stack_push(tempStack, temp, OPERATOR);
      }
    }
  }

  printf("Temp stack:\t");
  print_stack(tempStack);

  while (!stack_is_empty(tempStack)) {

    char tempOperator = stack_peek(tempStack)->symbol.op;
    Datum tempDatum = {.op = tempOperator};
    stack_pop(tempStack);
    stack_push(postfixStack, tempDatum, OPERATOR);
  }

  printf("Postfix stack:\t");
  print_stack(postfixStack);

  destroy_stack(tempStack);

  return postfixStack;
}


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
      printf("%c -> ", (char)node->symbol.op);
    } else {
      printf("%d -> ", (int)node->symbol.operand);
    }

    node = node->nextElem;
  }

  printf("\n");
}

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
