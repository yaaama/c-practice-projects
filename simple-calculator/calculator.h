#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

/* General mathematical functions */

/*  Will include helpful functions */
double add (int k, ...);

/* Will subtract k number of arguments from each other*/
double subtract(int k, ...);

/* Will multiply k number of arguments from each other*/
double multiply(int k, ...);

/* Will divide k number of arguments */
double divide(int k, ...);




/* Stack world! */

typedef enum  {
  OPERAND, OPERATOR, PARENS
} ELEMENT_TYPE;

typedef union {
  int operand;
  char op;
  char paren;
} Datum;

typedef struct {
 Datum data;
ELEMENT_TYPE type;
 void *nextElem;
} StackNode;

typedef struct {
  StackNode *top;
  int size;
  /* int empty; */
} Stack;


/* Pushing an element on the stack */
StackNode *stack_push(Stack *stack, Datum data, ELEMENT_TYPE type);

/* Popping the stack */
StackNode *stack_pop(Stack *stack);

/* Viewing the top element in the stack */
StackNode *stack_peek(Stack *stack);

/* Seeing if stack is empty */
bool stack_is_empty(Stack *stack);

/* Size of stack */
int stack_size(Stack *stack);

/* Printing elements of the stack */
void print_stack(Stack *stack);
