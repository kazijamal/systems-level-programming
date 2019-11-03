#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "songnode.h"

struct song_node * add_song(struct song_node ** library, char * name, char * artist) {
  printf("adding [%s: %s]\n", artist, name);
  int index = artist[0] - 'a';
  if (index > 25 || index < 0) {
    index = 26;
  }
  library[index] = insert_ordered(library[index], name, artist);
  return library[index];
}

struct song_node * search_song(struct song_node ** library, char * name, char * artist) {
  printf("looking for [%s: %s]\n", artist, name);
  int index = artist[0] - 'a';
  if (index > 25 || index < 0) {
    index = 26;
  }
  struct song_node * result = find_song(library[index], name, artist);
  if (result == NULL) {
    printf("song not found\n");
  }
  else {
    printf("song found! %s: %s\n", result->artist, result->name);
  }
  return result;
}

void print_letter(struct song_node ** library, char letter) {
  int index = letter - 'a';
  printf("%c list\n ", letter);
  print_list(library[index]);
}

void print_artist(struct song_node ** library, char * artist) {
  printf("Printing [%s]\n", artist);
  int index = artist[0] - 'a';
  if (index > 25 || index < 0) {
    index = 26;
  }
  struct song_node * list = find_artist_first(library[index], artist);
  if (list == NULL) {
    printf("no songs found by artist\n");
  }
  else {
    while (list != NULL && strcmp(list->artist, artist) == 0) {
      printf("[%s: %s]\n", list->artist, list->name);
      list = list->next;
    }
  }
}

void print_library(struct song_node ** library) {
  int index;
  for (index = 0; index < 27; index++) {
    char letter = index + 'a';
    if (index == 26) {
      letter = '~';
    }
    if (library[index] != NULL) {
      printf("%c list\n ", letter);
      print_list(library[index]);
    }
  }
}

void shuffle(struct song_node ** library, int n) {
  while (n > 0) {
    int index = rand() % 27;
    struct song_node * random_node = rand_node(library[index]);
    printf("[%s: %s]\n", random_node->artist, random_node->name);
    n--;
  }
}

void delete(struct song_node ** library, char * name, char * artist) {
  printf("removing: [%s: %s]\n", artist, name);
  int index = artist[0] - 'a';
  library[index] = remove_node(library[index], name, artist);
}

void clear(struct song_node ** library) {
  int index;
  for (index = 0; index < 27; index++) {
    library[index] = free_list(library[index]);
  }
}
