#include <stdio.h>
#include <stdlib.h>
#include "songnode.h"

int main() {
  struct song_node * list = NULL;
  print_list(list);
  list = insert_ordered(list, "no games", "dua lipa");
  print_list(list);
  list = insert_ordered(list, "flex", "mumble rapper");
  print_list(list);
  return 0;
}
