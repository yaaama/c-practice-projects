#ifndef CALCULATOR_H
#define CALCULATOR_H




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
 char symbol;
/* ELEMENT_TYPE type; */
 void *nextElem;
} StackNode;

typedef struct {
  StackNode *top;
  int size;
  /* int empty; */
} Stack;


/* Pushing an element on the stack.
  MALLOC used. */
StackNode *stack_push(Stack *stack, char symbol);

/* Popping the stack
   FREES popped node. */
StackNode *stack_pop(Stack *stack);

/* Viewing the top element in the stack */
StackNode *stack_peek(Stack *stack);

/* Seeing if stack is empty */
bool stack_is_empty(Stack *stack);

/* Size of stack */
int stack_size(Stack *stack);

/* Will destroy and free up all of the stack memory
  Will return 1 if success, else NULL
 TODO Implement this */
int destroy_stack(Stack *stack);

/* Printing elements of the stack */
void print_stack(Stack *stack);

/* Prints a string to standard output */
void print_string(char *str, int size);

/* TODO Remove from this header file later */
char *convert_to_postfix(char *expr, int size);

#endif //CALCULATOR_H
