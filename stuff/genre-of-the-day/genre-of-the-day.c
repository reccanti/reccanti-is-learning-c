#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  printf("%s\n", node->string);
}

void printList(LIST *head) {
  LIST *cur = head;
  while (cur != NULL) {
    printEntry(cur);
    cur = cur->next;
  }
}

int main(void) {

  // pointer to the list of genres file
  FILE *fptr;
  LIST *current;
  LIST *head;
  char line[128];

  current = NULL;
  head = NULL;
  fptr = fopen("./genres.txt", "r");

  while (fgets(line, sizeof(line), fptr)) {
    // printf("allocate node\n");
    LIST *node = malloc(sizeof(LIST));
    // printf("copy string\n");

    strcpy(node->string, line);
    // printf("assign next\n");
    node->next = NULL;

    if (head == NULL) {
      // printf("assign head\n");
      head = node;
      current = node;
    } else {
      // printf("assign cur\n");
      current->next = node;
      current = node;
    }
  }

  // LIST *node = getItemAtIndex(0, head);
  // printEntry(node);
  // node = getItemAtIndex(1, head);
  // printEntry(node);

  srand(time(NULL));
  int index = rand() % getLength(head);
  LIST *node = getItemAtIndex(index, head);
  printEntry(node);

  // printf("%i\n", index);
  // printf()

  // int length = getLength(head);

  // printList(head);
  freeList(head);
  fclose(fptr);

  return 0;
}