#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songnode.h"

struct song * insert_front(struct song * list, char name1[100], char artist1[100]) {
  struct song *new = malloc(1 * sizeof(struct song));
  new->name = name1;
  new->artist = artist1;
  new->next = list;
  return new;
}

struct song * insert_ordered(struct song * list, char name1[100], char artist1[100]) {
  struct song *front = list;
  struct song *new = malloc(1 * sizeof(struct song));
  new->name = name1;
  new->artist = artist1;
  while (list != NULL) {
    if (strcmp(list->next,name1) < 0) {
      new->next = list;
      return front;
    }
    list =  list->next;
  }
}
