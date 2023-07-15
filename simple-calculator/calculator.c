#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculator.h"
#include "zlog.h"

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
    /* printf("%c it is an operator\n", c); */
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
    /* printf("%c is a digit.\n", c); */
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

  /* printf("Pushed char %c to stack.\n", stack->top->symbol.op); */
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

  /* printf("Pushed integer %d to stack.\n", (int)stack->top->symbol.operand);
   */
}

StackNode *stack_push(Stack *stack, Datum datum, ELEMENT_TYPE type) {

  if (stack->top == NULL || stack_is_empty(stack)) {
    printf("Stack is empty!\n");
  }

  if (stack_size(stack) == STACK_LIM) {
    printf("Stack size is full! Exiting.");
    exit(0);
  }

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

StackNode *stack_pop(Stack *stack) {

  /* If the stack is not empty */
  /* New top of the stack will be the next element down */
  StackNode *currTop = stack->top;
  StackNode *newTop = currTop->nextElem;

  if (currTop->type == OPERATOR) {
    /* printf("Pop -> %c\n", currTop->symbol.op); */
  } else {
    /* printf("Pop -> %d\n", currTop->symbol.operand); */
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

  /* printf("Removing whitespace: \n"); */
  while (*untrimmedStr != '\0') {

    if (!isspace(*untrimmedStr)) {
      *trimmedStr = *untrimmedStr;
      /* printf("%c", *trimmedStr); */
      trimmedStr++;
    }

    untrimmedStr++;
  }

  /* printf("\n"); */
  *trimmedStr = '\0';
}

void expr_remove_parens(char *restrict untrimmedStr,
                        char *restrict trimmedStr) {

  /* printf("Removing parentheses: \n"); */
  int count = 0;
  while (*untrimmedStr != '\0') {

    if (*untrimmedStr != '(' && *untrimmedStr != ')') {
      *trimmedStr = *untrimmedStr;
      /* printf("%c", *trimmedStr); */
      count++;
      trimmedStr++;
    }

    untrimmedStr++;
  }

  /* printf("\n"); */
  *trimmedStr = '\0';
}

int calc_operation(char operator, int a, int b) {

  printf("calc_operation:\t%d %c %d", a, operator, b);

  switch (operator) {
  case '+':
    return (a + b);
  case '-':
    return (a - b);
  case '*':
    return (a * b);
  case '/':
    if (b == 0) {
      return 0;
    }
    return (a / b);
  default:
    return 0;
  }

  return 0;
}

Stack *reverse_stack(Stack *stack) {

  Stack *tempStack = malloc(sizeof(Stack));
  tempStack->size = 0;
  tempStack->top = NULL;

  while (!stack_is_empty(stack)) {
    Datum toPush = stack->top->symbol;
    ELEMENT_TYPE type = stack->top->type;
    stack_pop(stack);
    stack_push(tempStack, toPush, type);
  }

  return tempStack;
}

int postfix_evaluate(Stack *expression) {

  Stack *expr = reverse_stack(expression);
  if (stack_size(expr) == 0 || stack_is_empty(expr)) {
    printf("The answer to this is 0...\n");
    return 0;
  }

  Stack *resultStack = malloc(sizeof(Stack));

  resultStack->size = 0;
  resultStack->top = NULL;

  printf("\n\nEvaluation of postfix is starting...\n");
  while (!stack_is_empty(expr)) {

    StackNode *currNode = stack_peek(expr);

    if (currNode->type == OPERAND) {
      stack_push(resultStack, currNode->symbol, OPERAND);
      stack_pop(expr);
      continue;

    } else if (currNode->type == OPERATOR) {

      int a = stack_peek(resultStack)->symbol.operand;
      stack_pop(resultStack);
      int b = stack_peek(resultStack)->symbol.operand;
      stack_pop(resultStack);
      int result = calc_operation(currNode->symbol.op, b, a);
      printf("%d %c %d = %d", b, currNode->symbol.op, a, result);

      Datum resultD = {.operand = result};
      stack_push(resultStack, resultD, OPERAND);
      stack_pop(expr);
    }
  }
  int answer = resultStack->top->symbol.operand;
  printf("Answer is :\t%d\n", answer);
  return answer;
}

/* Converts given string into a postfix expression */
Stack *postfix_conversion(char *expr, int length) {

  char *wsRemoved = malloc(sizeof(char) * (length + 1));
  expr_remove_whitespace(expr, wsRemoved); /* Removes the whitespace */
  printf("postfix_conversion:\tRemoved whitespace:\t%s\n", wsRemoved);
  char *cleanExpr = malloc(sizeof(char) * (length + 1));
  expr_remove_parens(wsRemoved, cleanExpr);
  printf("postfix_conversion:\tRemoved parens:\t%s\n", cleanExpr);

  size_t leng = strlen(cleanExpr);
  leng += 1; /* Accounts for the null terminator */
  printf("postfix_conversion:\tOriginal length: %d , trimmed length: %zu\n",
         length, leng);

  Stack *postfixStack = malloc(sizeof(Stack));
  postfixStack->size = 0;
  postfixStack->top = NULL;
  Stack *tempStack = malloc(sizeof(Stack));
  tempStack->size = 0;
  tempStack->top = NULL;

  for (size_t i = 0; i < leng; i++) {

    int currentNumber = 0;
    char currentChar = cleanExpr[i];

    if (currentChar == '\0') { /* If the char is the null terminator then the
                                  expression is finished being read  */
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
        /* Pop op stack that has either the same or higher precedence than the
         * current op (charPrec) */
        while (charPrec <= tempTopPrec && !stack_is_empty(tempStack)) {

          stack_push(postfixStack, temp, OPERATOR);

          stack_pop(tempStack);

          if (stack_peek(tempStack) != NULL) {
            tempTopPrec = precedence(stack_peek(tempStack)->symbol.op);
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

  printf("postfix_conversion:\tTemp stack:\t");
  print_stack(tempStack);

  while (!stack_is_empty(tempStack)) {

    char tempOperator = stack_peek(tempStack)->symbol.op;
    Datum tempDatum = {.op = tempOperator};
    stack_push(postfixStack, tempDatum, OPERATOR);
    stack_pop(tempStack);
  }

  printf("Postfix stack:\t");
  print_stack(postfixStack);

  /* Freeing memory */
  destroy_stack(tempStack);
  free(cleanExpr);
  free(wsRemoved);

  return postfixStack;
}

int destroy_stack(Stack *stack) {

  /* printf("Destroying stack!\n"); */
  if (stack == NULL) {

    /* printf("Stack is NULL! Cannot destroy, returning error...\n"); */
    return 0;
  }

  while (stack->top != NULL) {
    stack_pop(stack);
  }

  free(stack);

  return 1;
}

StackNode *stack_peek(const Stack *stack) {

  if (stack->top == NULL) {
    /* printf("Stack is empty! Cannot peek."); */
    return NULL;
  }

  return stack->top;
}

bool stack_is_empty(const Stack *stack) {

  if (stack->top == NULL || stack_size(stack) == 0) {
    return true;
  }

  return false;
}

int stack_size(const Stack *stack) {

  if ((stack == NULL) || (stack->top == NULL)) {
    return 0;
  }

  return stack->size;
}

void print_stack(Stack *stack) {

  printf("---Printing stack!---\n");
  StackNode *node = stack->top;

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
