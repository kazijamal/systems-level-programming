#include <stdio.h>
#include <stdlib.h>
#include "songnode.h"

int main() {
  struct song_node * list = NULL;
  struct song_node * found = NULL;
  print_list(list);

  printf("testing adds to null list\n");
  list = insert_ordered(list, "no goodbyes", "dua lipa");
  print_list(list);

  printf("testing adds to front if 1st node has greater artist\n");
  list = insert_ordered(list, "pump it", "black eyed peas");
  print_list(list);

  printf("testing adds to front if 1st node has same artist, greater song\n");
  list = insert_ordered(list, "another song", "black eyed peas");
  print_list(list);

  printf("testing adds to end if greater artist\n");
  list = insert_ordered(list, "the end", "minecraft");
  print_list(list);

  printf("testing adds to end if same artist, greater song\n");
  list = insert_ordered(list, "the end?", "minecraft");
  print_list(list);

  printf("testing adds artist in right place\n");
  list = insert_ordered(list, "crazy", "gnarls barkley");
  print_list(list);

  printf("add a dua lipa song for future testing\n");
  list = insert_ordered(list, "idgaf", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (middle)\n");
  list = insert_ordered(list, "new rules", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (beginning)\n");
  list = insert_ordered(list, "be the one", "dua lipa");
  print_list(list);

  printf("testing adds song in right place (end)\n");
  list = insert_ordered(list, "one kiss", "dua lipa");
  print_list(list);

  printf("testing artist not found in beginning\n");
  found = find_artist_first(list, "acdc");
  print_list(found);

  printf("testing artist not found in middle\n");
  found = find_artist_first(list, "downstait");
  print_list(found);

  printf("testing artist not found in end\n");
  found = find_artist_first(list, "zz top");
  print_list(list);

  printf("testing found artist first song\n");
  found = find_artist_first(list, "dua lipa");
  print_list(found->name);

  return 0;
}
