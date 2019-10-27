#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
  struct node * testList = NULL;

  // testing print_list()
  printf("Printing empty list:\n");
  print_list(testList);

  printf("\n");

  // testing insert_front()
  printf("Adding #s 0-9 to list.\n");
  int i;
  for (i = 0; i <= 9; i++) {
    testList = insert_front(testList, i);
  } 
  printf("Printing list:\n");
  print_list(testList);

  printf("\n");
  
  // testing myRemove()
  printf("Removing 5 from list.\n");
  remove_node(testList, 5);
  print_list(testList);

  printf("\n");
  
  printf("Removing 9 from list.\n");
  remove_node(testList, 9);
  print_list(testList);

  printf("\n");
  
  printf("Removing 10 from list.\n");
  remove_node(testList, 10);
  print_list(testList);

  printf("\n");
  
  // testing free_list
  printf("Freeing list:\n");
  testList = free_list(testList);
  printf("Printing list:\n");
  print_list(testList);
  
  return 0;
}
