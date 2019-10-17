#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct phone examplePhone() {
  struct phone newPhone;
  char* manufacturers[6] = {"Apple","Samsung","Google","OnePlus","Huawei","LG"};
  newPhone.manufacturer = manufacturers[rand() % 6];
  newPhone.price = rand() % 1400 + 100;
  return newPhone;
}

void printPhone(struct phone p) {
  printf("phone -- manufacturer: %s, price: %d\n", p.manufacturer, p.price);
}

void modifyPhone(struct phone* p, char* newManufacturer, int newPrice) {
  p->manufacturer = newManufacturer;
  p->price = newPrice;
}
