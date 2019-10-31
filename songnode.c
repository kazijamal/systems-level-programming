#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songnode.h"

void print_list(struct song_node * list) {
  printf("[ ");
  while (list != NULL) {
    printf("%s : %s, ", list->artist, list->name);
    list = list->next;
  }
  printf("]\n");
}

struct song_node * insert_front(struct song_node * list, char name[100], char artist[100]) {
  struct song_node *new = malloc(sizeof(struct song_node));
  strcpy(new->name, name);
  strcpy(new->artist, artist);
  new->next = list;
  return new;
}

struct song_node * insert_ordered(struct song_node * list, char name1[100], char artist1[100]) {
  struct song_node *new = malloc(1 * sizeof(struct song_node));
  strcpy(new->name, name1);
  strcpy(new->artist, artist1);
  if (strcmp(list->artist,artist1) > 0) {
    return insert_front(list,name1,artist1);
  }
  struct song_node *curr = list;
  struct song_node *prev;
  while (curr != NULL) {
    if (strcmp(curr->artist,artist1) > 0) {
      new->next = curr;
      prev->next = new;
      return list;
    }
    if (strcmp(curr->artist,artist1) == 0) {
      while (curr != NULL) {
	if (strcmp(curr->name,name1) < 0) {
	  new->next = curr;
	  prev->next = new;
	  return list;
	}
	prev = curr;
	curr = curr->next;
      }
    }
    prev = curr;
    curr = curr->next;
  }
  prev->next = new;
  new->next = NULL;
  return list;
}
