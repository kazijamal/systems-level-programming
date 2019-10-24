#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
  struct node * testList = malloc(sizeof(struct node));
  testList = NULL;

  // testing print_list()
  printf("Printing empty list:\n");
  print_list(testList);

  // testing insert_front()
  printf("Adding #s 0-9 to list.\n");
  int i;
  for (i = 0; i <= 9; i++) {
    testList = insert_front(testList, i);
  } 
  printf("Printing list:\n");
  print_list(testList);

  // testing free_list
  printf("Freeing list:\n");
  testList = free_list(testList);
  printf("Printing list:\n");
  print_list(testList);
  
  return 0;
}
