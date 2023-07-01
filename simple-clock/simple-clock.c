#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

  int hour;
  int minute;
  int second;
  char meridiem[3];

} Time;

/* Meant to handle interrupt signal by closing program
  Unfortunately does not work as expected, will need to look into this */
void handleSignal(int signal) {
  printf("Got a signal %d", signal);
  exit(0);
}

/* Prints error messages if user types wrong inputs
  1 is error for hour, 2 is for minute, 3 is seconds
 and 4 is for AM and PM */
void print_error(int code) {

  switch (code) {
  case 1:
    printf("You have incorrectly typed the hour, it should be between 0 and "
           "11.\n");
    break;
  case 2:
    printf("You have incorrectly typed the minute, it should be between 0 and "
           "60.\n");
    break;
  case 3:
    printf("You have incorrectly typed the second, it should be between 0 and "
           "60.\n");
    break;
  case 4:
    printf("You have incorrectly written the meridiem. It should either be "
           "\"AM\" or \"PM\"\n");
    break;
  default:
    printf("Somethings gone wrong, time to exit.\n");
    exit(1);
    break;
  }

  printf("Please try again!\n");
}

int check_meridiem_input(char *meridiem) {

  if (strlen(meridiem) != 2) {
    return 1;
  }

  if ((strcasecmp(meridiem, "AM") == 0)) {

    return 2;
  }

  if (strcasecmp(meridiem, "PM") == 0) {
    return 3;
  }

  return 0;
}

int main() {

  signal(SIGINT, handleSignal); /* For some reason the signal does not register
                                   inside of the while loop
                                   This means the program does not terminate
                                   with Control C */

  Time time = {};
  int delay = 1000;               /* Delay will be 1000 ms (1 second) */
  char *sleepCommand = "sleep 1"; /* Sleep command for 1 second */

  char meridInp[3];
  while (1) {

    printf(
        "Please enter the current time in the format HOUR MIN SECOND AM/PM \n");
    int correctInp = scanf("%d %d %d %s", &time.hour, &time.minute,
                           &time.second, time.meridiem);

    if (correctInp != 4) {
      printf("You have not written a correct time!\n");
      scanf("%*s");
      continue;
    }

    if (time.hour > 12 || time.hour < 0) {
      print_error(1);
      scanf("%*s");
      continue;
    }
    if (time.minute > 60 || time.minute < 0) {
      print_error(2);
      scanf("%*s");
      continue;
    }
    if (time.second > 60 || time.second < 0) {
      print_error(3);
      scanf("%*s");
      continue;
    }
    if (check_meridiem_input(time.meridiem) == 1) {
      print_error(4);
      scanf("%*s");
      continue;
    }

    break;
  }

  int count = 0; /* Delete later */

  while (count < 10) {

    if (time.second == 60) {
      time.second = 0;
      time.minute++;
    }
    if (time.minute == 60) {
      time.minute = 0;
      time.hour++;
    }
    if (time.hour == 13) {
      time.hour = 0;
      // Need to change AM and PM
      if (check_meridiem_input(time.meridiem) == 2) {
        strcpy(time.meridiem, "PM");
      } else {
        strcpy(time.meridiem, "AM");
      }
    }

    printf("Time currently: ");
    printf("%d : %d : %d : %s\n", time.hour, time.minute, time.second,
           time.meridiem);

    signal(SIGINT, handleSignal); /* This does not work! */

    system(sleepCommand);
    /* system("clear"); */

    time.second++;
    count++;
  }

  return 0;
}
