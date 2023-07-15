#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "calculator.h"
#include <ctype.h>

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

bool validate_expression(char *exp) {

  bool valid = true;
  size_t numOperations = 0;
  size_t operands = 0;


/*TODO: Ensure boundary cases are properly handled */
  while (*exp != '\0') {

    if (exp == NULL) {
      return false;
    } else if (isblank(*exp)) {
      return false;
    }
    else if (is_operator(*exp)) {
      numOperations += 1;
    } else if (is_digit(*exp)) {
      operands += 1;
    } else if (isspace(*exp)) {
      exp ++;
      continue;
    } else if (!is_operator(*exp) && !is_digit(*exp)) {
      return false;
    }
    exp++;
  }

  return valid;
}

void enter_expression_mode() {

  size_t chars_read;
  size_t expSize = 0;
  char *expression;

  printf("Please enter 'q' to escape back to the main menu.\n");

  while (true) {
    printf("Enter the expression you would like to evaluate:\n");
    chars_read = getline(&expression, &expSize, stdin);

    if (chars_read < 0) {
      printf("couldn't read the input\n");
      free(expression);
      return;
    } else if (*expression == 'q') {
      printf("You are quitting!\n");
      return;

    } else if (!validate_expression(expression)) {
      printf("You have mistyped the expression! Please try again.\n");
      continue;
    } else {
      expression_handler(expression);
      continue;
    }
  }
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
      enter_expression_mode();
    case 3:
      print_user_options();
      break;
    }
  }

  return 0;
}
