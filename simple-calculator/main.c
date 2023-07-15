#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "calculator.h"
/* #include "zlog.h" */

void print_user_options() {

  printf("The options you have available to you are:\n");
  printf("\t1: Quit\n");
  printf("\t2: Evaluate an expression.\n");
  printf("\t3: Show help.\n");
}

void expression_handler(char *input) {

  Stack *stack = postfix_conversion(input, strlen(input));
  postfix_evaluate(stack);
}

int main(int argc, char *argv[]) {

  char *expression = NULL; /* This is where the expression will be stored */
  size_t expSize = 0;
  size_t chars_read;

  printf("Welcome! This is a simple calculator you can use to evaluate "
         "expressions.\n");

  int option;
  bool exprValid = false;

  while (option != 1) {

    print_user_options();

    char *tmp;
    size_t optionSize = 0;

    int success = getline(&tmp, &optionSize, stdin);
    int option = atoi(tmp);

    /* Will return if input is not correct */
    if (success < 0) {
      printf("Incorrect input, closing program.\n");
      return 1;
    }

    switch (option) {
    case 1:
      printf("See ya buddy.\n");
      exit(1);

    case 2:
      printf("Please enter the expression you would like to evaluate:\n");
      chars_read = getline(&expression, &expSize, stdin);
      printf("expression read: %s\n", expression);

      if (chars_read < 0) {
        printf("couldn't read the input\n");
        free(expression);
        return 1;
      } else {
        expression_handler(expression);
        continue;
      }
      break;
    case 3:
      print_user_options();
      break;
    }
  }

  return 0;
}
