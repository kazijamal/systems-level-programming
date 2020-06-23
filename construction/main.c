#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main() {
  srand(time(NULL));

  struct phone newPhone;

  printf("These are five examples of a phone struct, generated with the examplePhone() function and printed with the printPhone() function:\n");
  int i;
  for (i = 1; i <= 6; i++){
    newPhone = examplePhone();
    printPhone(newPhone);
  }

  printf("\n");

  printf("This is the phone that will be modified by the modifyPhone() function:\n");
  struct phone modPhone = examplePhone();
  printPhone(modPhone);
  struct phone *p = &modPhone;
  printf("\nThis is the phone after being modified by the modifyPhone() function:\n");
  modifyPhone(p, "Pear", 9999);
  printPhone(modPhone);
  
  return 0;
}
  
