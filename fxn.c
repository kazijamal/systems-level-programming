#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void print_list(struct node * n) {
  printf("[ ");
  while (n != NULL) {
    printf("%d ", n->i);
    n = n->next;
  }
  printf("]\n");
}

struct node * insert_front(struct node * n, int i) {
  struct node * newNode = malloc(sizeof(struct node));
  newNode->i = i;
  newNode->next = n;
  return newNode;
}

struct node * free_list(struct node * n) {
  while (n != NULL) {
    printf("freeing node: %d\n", n->i);
    struct node * currentNode = n;
    n = n->next;
    free(currentNode);
    currentNode = NULL;
  }
  return n;
}

struct node * remove2_node(struct node * front, int data) {
  struct node * current = front;
  struct node * previous = NULL;
  while (current != NULL) {
    if (current->i == data) {
      struct node * removeNode = current;
      if (previous == NULL) front = front->next;
      else previous->next = removeNode->next;
      free(removeNode);
      removeNode = NULL;
    }
    previous = current;
    current = current->next;
  }
  return front;
}
