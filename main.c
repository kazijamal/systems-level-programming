#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
  struct node testList;
  struct node *p = &testList;
  
  printf("Printing empty list:\n");
  print_list(p);

  printf("Adding #s 0-9 to list.\n");
  printf("Printing list:\n");
  print_list(p);

  printf("Freeing list:\n");

  printf("Printing list:\n");
  print_list(p);
  
  return 0;
}
