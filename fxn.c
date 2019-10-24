#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void print_list(struct node * n) {
  char* ans = "[ ";
  while (n != NULL) {
    int i = n->i;
    strcat(ans, i);
    strcat(ans, " ");
  }
  strcat(ans, "]");
  printf("%s\n", ans);
}

struct node * insert_front(struct node * n, int i) {
  
}

struct node * free_lilst(struct node * n) {
  
}
