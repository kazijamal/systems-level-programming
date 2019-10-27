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

struct node * remove_node(struct node * front, int data) {
  struct node * current = front;
  if (current == NULL) return front;
  if (current->i == data) {
    front = front->next;
    free(current);
    return front;
  }
  while (current->next != NULL) {
    if (current->next->i == data) {
      struct node* removeNode = current->next;
      current->next = removeNode->next;
      free(removeNode);
      return front;
    }
    current = current->next;
  }
  return front;
}
