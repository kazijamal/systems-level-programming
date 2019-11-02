#include <stdio.h>
#include <stdlib.h>
#include "songnode.h"

int main() {
  struct song_node * list = NULL;
  print_list(list);

  printf("testing adds to null list");
  list = insert_ordered(list, "no goodbyes", "dua lipa");
  print_list(list);

  printf("testing adds to front if 1st node has greater artist");
  list = insert_ordered(list, "pump it", "black eyed peas");
  print_list(list);

  printf("testing adds to front if 1st node has same artist, greater song");
  list = insert_ordered(list, "another song", "black eyed peas");
  print_list(list);

  printf("testing adds to end if greater artist");
  list = insert_ordered(list, "the end", "minecraft");
  print_list(list);

  printf("testing adds to end if same artist, greater song");
  list = insert_ordered(list, "the end?", "minecraft");
  print_list(list);

  printf("testing adds artist in right place");
  list = insert_ordered(list, "crazy", "gnarls barkley");
  print_list(list);

  printf("add a dua lipa song for future testing");
  list = insert_ordered(list, "idgaf", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (middle)");
  list = insert_ordered(list, "new rules", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (beginning)");
  list = insert_ordered(list, "be the one", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (end)");
  list = insert_ordered(list, "one kiss", "dua lipa");
  print_list(list);

  return 0;
}
