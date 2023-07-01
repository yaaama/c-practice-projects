#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  void *nextNode;
} Node;

typedef struct {
  Node *head;
  int size;
} LinkedList;

/* Create new linked list */

LinkedList *create_new_list() {

  LinkedList *newList = malloc(sizeof(LinkedList));
  newList->size = 1;

  return newList;
}

/* Add new node to the linked list (to the head) */

Node *add_node_to_head(LinkedList *list, int data) {

  Node *node = NULL;

  if (list->head == NULL) { /* If list is empty then create new node*/

    node = malloc(sizeof(Node));
    if (node == NULL) { /* If malloc fails then return... */
      printf("Error has happened...");
      return NULL;
    }
    node->data = data;
    list->head = node;
    list->size = 1; /* Empty list now has size of 1 because new node */
    list->head->nextNode = NULL;
  } else {

    node = malloc(sizeof(Node));
    node->data = data;
    node->nextNode = list->head;
    list->head = node;
    list->size += 1;
  }
  return node;
}

/* Remove a node from the list, 1 if success, 0 if fail */
int remove_node(LinkedList *list, int data) {

  Node *currentNode = list->head;
  Node *previousNode = list->head;

  if (currentNode->data == data) {
    list->head = currentNode->nextNode;
    list->size -= 1;
    free(currentNode);
    return 1;
  }

  while (currentNode != NULL) {

    if (currentNode->data == data) {
      /* When we find the node with the data we want to remove */

      if (currentNode == list->head) {
        list->head = currentNode->nextNode;
      }

      previousNode->nextNode = currentNode->nextNode;
      free(currentNode);
      list->size -= 1;
      return 1;
    }
    previousNode = currentNode;
    currentNode = currentNode->nextNode;
  }

  return 0;
}

/* Get the size of the list */
int get_size_of_list(LinkedList *list) { return list->size; }

/* Print list */
void print_linked_list(LinkedList *list) {

  Node *currentNode = list->head;

  while (currentNode != NULL) {

    printf("%d -> ", currentNode->data);
    currentNode = currentNode->nextNode;
  }
  printf(" EMPTY \n");
}

void wipe_list(LinkedList *list) {

  Node *currentNode = list->head;
  Node *toRemove = list->head;

  while (currentNode != NULL) {
    toRemove = currentNode;
    currentNode = currentNode->nextNode;
    list->size -= 1;
    free(toRemove);
  }

  list->head = NULL;
}

void print_user_options() {

  printf("Here are your user options:\n");
  printf("\t 1: Destroy the current list and create a new one.\n");
  printf("\t 2: Add new node to the head of the list.\n");
  printf("\t 3: Remove a node with a specified data value.\n");
  printf("\t 4: Get the size of the list.\n");
  printf("\t 5: Print the contents of the list.\n");
  printf("\t 6: Exit the program.\n");
}

int main() {

  int option = -1;
  LinkedList *list =
      malloc(sizeof(LinkedList)); /* Creating a new linked list */

  while (option != 6) {
    print_user_options();

    int optReceived = scanf("%d", &option);

    if (optReceived != 1) {
      printf("Incorrect input, closing program.\n");
      return 1;
    }

    if (optReceived == 1) { /* Scanf will return a 1 if it has succesfully read
                               a single input */
      switch (option) {

      case 1:
        /* Destroy list and create new one */
        wipe_list(list);
        printf("Removed all elements from the linked list! It looks like this "
               "now:\n");
        print_linked_list(list);
        break;

      case 2: {
        int dataToAdd = 0;
        printf("Please enter the data you would like to add for the node:\n");
        scanf("%d", &dataToAdd);
        /* adding new node to the head */
        if (add_node_to_head(list, dataToAdd) != NULL) {
          printf("Node added succesfully!\n");
        }

      } break;

      case 3: {
        /* removing a node from the list */
        printf("What data value would you like to remove from the list?\n");
        int toRemove = 0;
        scanf("%d", &toRemove);
        if (remove_node(list, toRemove) == 1) {
          printf("Remove was a success! Here is the new list.\n");
          print_linked_list(list);
        } else {
          printf("Unsuccessful removal...\n");
        }
      } break;
      case 4:
        /* getting the size of the list */
        printf("List currently stores %d elements.\n", get_size_of_list(list));
        break;
      case 5:
        /* printing the list */
        printf("Here is the list printed:\n");
        print_linked_list(list);
        break;

      case 6:
        /* quitting the program */
        wipe_list(list);
        free(list);
        return 0;
        break;
      default:
        printf("Whoops! You've written something weird there buddy.\n");
        /* handle default case */
        return 1;
        break;
      }
    }
  }

  return 0;
}
