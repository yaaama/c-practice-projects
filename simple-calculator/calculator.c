#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "calculator.h"

/* Numb of elements allowed in a single stack */
#define STACK_LIM 100
/* Number of digits allowed in a numb */
#define DIGIT_LIM 10

/* Returns precedence of different operators */
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

/* Func to validate char is an acceptable operator or not */
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

/* Checks if a number is a digit or not */
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

/* Pushes characters into the stack */
void push_character(Stack *stack, char datum) {

  /* Datum union type stores the character */
  Datum data = {.op = datum};

  /* Creates new node to add to the stack given */
  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->type = OPERATOR;
  newNode->symbol = data;

  /* Swaps nodes around so the new node is on top */
  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  /* printf("Pushed char %c to stack.\n", stack->top->symbol.op); */
}

/* Pushes a number */
void push_number(Stack *stack, int datum) {

  /* Datum union type stores the number */
  Datum data = {.operand = datum};

  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->type = OPERAND;
  newNode->symbol = data;

  /* Swaps nodes around so the new node is on top */
  StackNode *tempNode = NULL;
  tempNode = stack->top;
  newNode->nextElem = tempNode;
  stack->top = newNode;

  /* printf("Pushed integer %d to stack.\n", (int)stack->top->symbol.operand);
   */
}

StackNode *stack_push(Stack *stack, Datum datum, ELEMENT_TYPE type) {

  assert(stack_size(stack) < STACK_LIM);

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

  /* print_stack(stack, "stack_push"); */

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

  /* print_stack(stack, "stack_pop"); */

  /* Returning the new top element in the stack */
  return stack->top;
}

void clean_expr(char *restrict untrimmedStr, char *restrict trimmedStr) {

  /* printf("Removing parentheses and whitespace...\n"); */

  while (*untrimmedStr != '\0') {

    if (!isspace(*untrimmedStr) &&
        (*untrimmedStr != '(' && *untrimmedStr != ')')) {
      *trimmedStr = *untrimmedStr;
      trimmedStr++;
    }
    untrimmedStr++;
  }

  *trimmedStr = '\0';
}

/* Takes two integers and applies an operation to them */
int calc_operation(char operator, int a, int b) {

  assert(is_operator(operator));

  /* printf("calc_operation:\t%d %c %d", a, operator, b); */

  switch (operator) {
  case '+':
    return (a + b);
  case '-':
    return (a - b);
  case '*':
    return (a * b);
  case '/':
    /* Making sure you don't divide by 0 */
    if (b == 0) {
      return 0;
    }
    return (a / b);
  default:
    return 0;
  }

  return 0;
}

/* Initialises a stack */
Stack *init_empty_stack(Stack *stackPtr) {

  stackPtr->size = 0;
  stackPtr->top = NULL;

  return stackPtr;
}

/* Reverses a stack using another stack
 * Returns a pointer to a new stack after
 * freeing the old one */
Stack *reverse_stack(Stack *stack) {

  Stack *reversed = malloc(sizeof(Stack));
  init_empty_stack(reversed);
  ELEMENT_TYPE type;
  Datum toPush;

  while (!stack_is_empty(stack)) {
    type = stack->top->type;
    toPush = stack->top->symbol;
    stack_pop(stack);
    stack_push(reversed, toPush, type);
  }

  assert(reversed != NULL);

  destroy_stack(stack);

  return reversed;
}

/* Evaluates an expression stored in a stack and returns the answer */
int postfix_evaluate(Stack *expression) {

  /* The expression we will work on */
  /* printf("\nReversing the stack.\n"); */
  Stack *expr = reverse_stack(expression);

  /* If the stack received is empty then we return 0 */
  if (stack_size(expr) == 0 || stack_is_empty(expr)) {
    printf("The answer to this is 0...\n");
    destroy_stack(expression);
    destroy_stack(expr);
    return 0;
  }

  /* Where the operands will be stored */
  Stack *resultStack = malloc(sizeof(Stack));
  init_empty_stack(resultStack);

  /* printf("\n\nEvaluating the post fix expression...\n"); */
  while (!stack_is_empty(expr)) {

    /* Current element of the expression */
    StackNode *currNode = stack_peek(expr);

    assert(currNode != NULL);

    /* If operand then we push into the result stack */
    if (currNode->type == OPERAND) {
      stack_push(resultStack, currNode->symbol, OPERAND);
      stack_pop(expr);
      continue;

    } else if (currNode->type == OPERATOR) {

      /* @a and @b are the operands and @result is the output of the operation
       *applied to the pair */
      int a = stack_peek(resultStack)->symbol.operand;
      stack_pop(resultStack);
      int b = stack_peek(resultStack)->symbol.operand;
      stack_pop(resultStack);
      int result = calc_operation(currNode->symbol.op, b, a);

      /* printf("%d %c %d = %d\n", b, currNode->symbol.op, a, result); */

      /* Pushing the output to the result stack */
      Datum resultD = {.operand = result};
      stack_push(resultStack, resultD, OPERAND);
      /* Popping the expr stack because we have finished with the top node */
      stack_pop(expr);
    }
  }

  int answer = resultStack->top->symbol.operand;
  destroy_stack(resultStack);
  printf("\nResult:\t%d\n\n", answer);
  return answer;
}

/* Converts given string into a postfix expression */
Stack *postfix_conversion(char *expr, int length) {

  /* Removing whitespace and any parantheses... */
  char *cleanExpr = malloc(sizeof(char) * (length + 1));
  clean_expr(expr, cleanExpr);
  /* printf("Cleaned up expression:\t%s\n", cleanExpr); */
  free(expr);

  /* Length of the cleaned up expression */
  size_t exprLeng = strlen(cleanExpr);
  exprLeng += 1; /* Accounts for the null terminator */

  /* printf("postfix_conversion:\tOriginal length: %d , trimmed length: %zu\n", */
  /*        length, exprLeng); */

  Stack *exprStack = malloc(sizeof(Stack));
  init_empty_stack(exprStack);
  Stack *operatorStack = malloc(sizeof(Stack));
  init_empty_stack(operatorStack);

  /* Counting how many characters we have gone through */
  int count = 0;

  char currentChar = *cleanExpr;
  for (int i = 0; i < exprLeng; i++) {

    int currentNumber = 0;
    currentChar = cleanExpr[i];

    if (currentChar == '\0') {
      break;
    }

    if (is_digit(currentChar)) {

      while (is_digit(currentChar) && i < exprLeng) {
        /* Accumulating the digits for multi digit numbers */
        currentNumber = (int)currentNumber * 10 + (currentChar - '0');
        i++;
        currentChar = cleanExpr[i];
      }

      Datum temp = {.operand = currentNumber};
      stack_push(exprStack, temp, OPERAND);
      i--;

      /* When the scanned character is an operator */
    } else if (is_operator(currentChar)) {

      /* If the operand stack is empty then you HAVE to push to it */
      if (operatorStack->top == NULL) {
        Datum temp = {.op = currentChar};
        stack_push(operatorStack, temp, OPERATOR);
        continue;
      }

      /* Pop from stack to the output while top of stack has the same or greater
       * precedence */
      int opStkPrec = precedence(stack_peek(operatorStack)->symbol.op);
      int currOpPrec =
          precedence(currentChar); /* This is the current operator
                                     being read from the expression */

      /* If the current operator in the stack is higher precedence than the one
       * on the being read from the expression we need to pop it (high prec
       * operator) and it put it into the expression stack */
      if (currOpPrec <= opStkPrec) {

        Datum highPrecOperator = stack_peek(operatorStack)->symbol;
        Datum lowPrecOperator = {.op = currentChar};

        while (currOpPrec <= opStkPrec && !stack_is_empty(operatorStack)) {

          stack_push(exprStack, highPrecOperator, OPERATOR);
          stack_pop(operatorStack);

          if (stack_peek(operatorStack) != NULL) {
            opStkPrec = precedence(stack_peek(operatorStack)->symbol.op);
            highPrecOperator = stack_peek(operatorStack)->symbol;
          }
        }
        stack_push(operatorStack, lowPrecOperator, OPERATOR);
      } else {
        Datum temp = {.op = currentChar};
        stack_push(operatorStack, temp, OPERATOR);
      }
    }
  }

  /* print_stack(operatorStack, "postfix_conversion::operatorStack"); */

  /* Now just adding in the remaining operators left on the operator stack */
  while (!stack_is_empty(operatorStack)) {
    /* Getting the operator on top... */
    char tempOperator = stack_peek(operatorStack)->symbol.op;
    /* Converting to a datum... */
    Datum tempD = {.op = tempOperator};
    /* Pushing it on the expression stack.. */
    stack_push(exprStack, tempD, OPERATOR);
    /* Popping it out of the operator stack... */
    stack_pop(operatorStack);
  }

  /* print_stack(exprStack, "postfix_conversion::exprStack"); */

  /* Freeing memory */
  destroy_stack(operatorStack);
  free(cleanExpr);

  return exprStack;
}

/* Used to free up mem taken by stack */
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

/* Peeks at the top item in the stack */
StackNode *stack_peek(const Stack *stack) {

  if (stack->top == NULL) {
    /* printf("Stack is empty! Cannot peek."); */
    return NULL;
  }

  return stack->top;
}

bool stack_is_empty(const Stack *stack) {

  if (stack_peek(stack) == NULL || stack_size(stack) == 0) {
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

void print_stack(Stack *stack, char *name) {

  StackNode *node = stack->top;

  printf("%s\tTop -> ", name);

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
