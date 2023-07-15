#ifndef CALCULATOR_H
#define CALCULATOR_H

/* General mathematical functions */

/* Stack world! */

typedef enum { OPERAND, OPERATOR } ELEMENT_TYPE;

typedef union {
  int operand;
  char op;
} Datum;

typedef struct {
  Datum symbol;
  ELEMENT_TYPE type;
  void *nextElem;
} StackNode;

typedef struct {
  StackNode *top;
  int size;
} Stack;

int precedence(char op);

bool is_digit(char c);

bool is_operator(char c);

/* Pushing an element on the stack.
  MALLOC used. */
StackNode *stack_push(Stack *stack, Datum datum, ELEMENT_TYPE type);

/* Popping the stack
   FREES popped node. */
StackNode *stack_pop(Stack *stack);

/* Viewing the top element in the stack */
StackNode *stack_peek(const Stack *stack);

/* Seeing if stack is empty */
bool stack_is_empty(const Stack *stack);

/* Size of stack */
int stack_size(const Stack *stack);

/* Will destroy and free up all of the stack memory
  Will return 1 if success, else NULL
 TODO Implement this */
int destroy_stack(Stack *stack);

/* Printing elements of the stack */
void print_stack(Stack *stack, char *name);

/* TODO Remove from this header file later */
Stack *postfix_conversion(char *expr, int size);

/* Evaluating the expression returned from convert_to_postfix */
int postfix_evaluate(Stack *expr);

#endif // CALCULATOR_H
