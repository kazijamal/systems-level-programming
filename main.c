#include <stdio.h>
#include <stdlib.h>
#include "songnode.h"

int main() {
  struct song_node * list = NULL;
  print_list(list);

  printf("testing adds to null list");
  list = insert_ordered(list, "no games", "dua lipa");
  print_list(list);

  printf("testing adds to front if 1st node has greater artist");
  list = insert_ordered(list, "pump it", "black eyed peas");
  print_list(list);

  printf("testing adds to front if 1st node has same artist, greater song");
  list = insert_ordered(list, "another song", "black eyed peas");
  print_list(list);

  return 0;
}
