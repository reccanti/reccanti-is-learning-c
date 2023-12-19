#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// string functions

void stripCharacters(char dest[], char string[]) {
  int strippedIndex = 0;
  for (int i = 0; i < strlen(string); i++) {
    char cur = string[i];
    switch (cur) {
      case '\n':
      case '\r':
      case '\0':
        break;
      default:
        dest[strippedIndex] = cur;
        strippedIndex++;
        break;
    }
  }
  dest[strippedIndex] = '\0';
}

// Linked List and methods

struct list {
  char string[128];
  struct list *next;
};
typedef struct list LIST;

LIST* getItemAtIndex(int index, LIST *head) {
  LIST *cur = head;
  for(int i = 0; i < index; i++) {
    cur = cur->next;
  }
  return cur;
}

int getLength(LIST *head) {
  int count = 0;
  LIST *cur = head;
  while (cur != NULL) {
    cur = cur->next;
    count++;
  }
  return count;
}

void freeList(LIST *head) {
  LIST *cur = head;
  LIST *temp;
  while (cur != NULL) {
    temp = cur;
    cur = cur->next;
    free(temp);
  }
}

// for debugging

void printEntry(LIST *node) {
  char stripped[128];
  stripCharacters(stripped, node->string);
  printf("%s\n", stripped);
}

void printList(LIST *head) {
  LIST *cur = head;
  while (cur != NULL) {
    printEntry(cur);
    cur = cur->next;
  }
}

// main script 

int main(void) {

  // pointer to the list of genres file
  FILE *fptr;

  // pointers to the head of the linked list we're going to construct, as well
  // as the current node as we construct it
  LIST *current;
  LIST *head;

  current = NULL;
  head = NULL;

  // the string that will hold the line as we parse it
  char line[128];

  // open the file and construct the linked list from each line
  fptr = fopen("./genres.txt", "r");
  while (fgets(line, sizeof(line), fptr)) {
    LIST *node = malloc(sizeof(LIST));

    strcpy(node->string, line);
    node->next = NULL;

    if (head == NULL) {
      head = node;
      current = node;
    } else {
      current->next = node;
      current = node;
    }
  }
  fclose(fptr);

  // get a random item from the linked list
  srand(time(NULL));
  int index = rand() % getLength(head);
  LIST *node = getItemAtIndex(index, head);
  printEntry(node);

  // clean up the list when we're done (not sure if this is necessary)
  freeList(head);

  return 0;
}