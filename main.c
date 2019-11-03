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

  printf("\ntesting find artist method:\n");
  printf("testing artist not found in beginning\n");
  found = find_artist_first(list, "acdc");
  printf("%p\n",found);

  printf("testing artist not found in middle\n");
  found = find_artist_first(list, "downstait");
  printf("%p\n",found);

  printf("testing artist not found in end\n");
  found = find_artist_first(list, "zz top");
  printf("%p\n",found);

  printf("testing found artist first song\n");
  found = find_artist_first(list, "dua lipa");
  printf("%s:%s\n\n",found->artist,found->name);


  printf("testing find song method:\n");
  printf("testing artist not found in beginning\n");
  found = find_song(list, "highway to hell", "acdc");
  printf("%p\n",found);

  printf("testing artist not found in middle\n");
  found = find_song(list, "avengers theme song", "downstait");
  printf("%p\n",found);

  printf("testing artist not found in end\n");
  found = find_song(list, "la grange", "zz top");
  printf("%p\n",found);

  printf("testing song not found in beginning\n");
  found = find_song(list, "a", "dua lipa");
  printf("%p\n",found);

  printf("testing song not found in middle\n");
  found = find_song(list, "f", "dua lipa");
  printf("%p\n",found);

  printf("testing song not found in end\n");
  found = find_song(list, "zzzz", "minecraft");
  printf("%p\n",found);

  printf("testing song found\n");
  found = find_song(list, "new rules", "dua lipa");
  printf("%s:%s\n",found->artist,found->name);

  printf("\ntesting removal method:\n");
  printf("removing from middle (dua lipa : one kiss)\n");
  list = remove_node(list,"one kiss","dua lipa");
  print_list(list);

  printf("removing from end (minecraft : the end?)\n");
  list = remove_node(list,"the end?","minecraft");
  print_list(list);

  printf("removing something not in list (ooga booga : ooga booga)\n");
  list = remove_node(list,"ooga booga","ooga booga");
  print_list(list);

  printf("removing from beginning of list (black eyed peas: another song)\n");
  list = remove_node(list,"another song","black eyed peas");
  print_list(list);

  srand(time(0));
  printf("testing random node method:\n");
  found = rand_node(list);
  printf("%s:%s\n",found->artist,found->name);
  found = rand_node(list);
  printf("%s:%s\n",found->artist,found->name);
  found = rand_node(list);
  printf("%s:%s\n",found->artist,found->name);

  printf("\njailbreak:\n");
  list = free_list(list);
  print_list(list);

  return 0;
}
