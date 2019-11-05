#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "songnode.h"
#include "library.h"

int main() {
  printf("LINKED LIST TESTS\n");
  printf("====================================\n\n");
  
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
  printf("====================================\n\n");

  printf("testing adds artist in right place\n");
  list = insert_ordered(list, "crazy", "gnarls barkley");
  print_list(list);

  printf("add a dua lipa song for future testing\n");
  list = insert_ordered(list, "idgap", "dua lipa");
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
  printf("====================================\n\n");

  printf("testing find artist method:\n");
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
  printf("====================================\n\n");

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
  printf("====================================\n\n");

  printf("testing removal method:\n");
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
  printf("====================================\n\n");

  srand(time(NULL));
  printf("testing random node method:\n");
  found = rand_node(list);
  printf("%s: %s\n",found->artist,found->name);
  found = rand_node(list);
  printf("%s: %s\n",found->artist,found->name);
  found = rand_node(list);
  printf("%s: %s\n",found->artist,found->name);
  printf("====================================\n\n");

  printf("jailbreak:\n");
  list = free_list(list);
  print_list(list);
  printf("====================================\n\n");

  printf("MUSIC LIBRARY TESTS\n\n");
  printf("====================================\n\n");

  struct song_node * table[27];
  int index;
  for (index = 0; index < 27; index++) {
    table[index] = NULL;
  }

  printf("Testing add_song\n");
  add_song(table, "thunderstruck", "ac/dc");
  add_song(table, "alive", "pearl jam");
  add_song(table, "even flow", "pearl jam");
  add_song(table, "yellow ledbetter", "pearl jam");
  add_song(table, "time", "pink floyd");
  add_song(table, "peaches", "presidents of the united states of america");
  add_song(table, "paranoid android", "radiohead");
  add_song(table, "street spirit (fade out)", "radiohead");
  printf("====================================\n\n");

  printf("Testing print_library\n");
  print_library(table);
  printf("====================================\n\n");

  printf("Testing print_letter\n");
  print_letter(table, 'p');
  printf("====================================\n\n");

  printf("Testing search_song\n");
  search_song(table, "alive", "pearl jam");
  search_song(table, "time", "pearl jam");
  printf("====================================\n\n");

  printf("Testing delete\n");
  delete(table, "alive", "pearl jam");
  print_library(table);
  printf("\n");
  delete(table, "yellow ledbetter", "pearl jam");
  print_library(table);
  printf("====================================\n\n");

  printf("Testing clear\n");
  clear(table);
  
  printf("Library after clear:\n\n");
  printf("====================================\n\n");

  printf("Adding songs to empty library\n");
  add_song(table, "thunderstruck", "ac/dc");
  add_song(table, "alive", "pearl jam");
  add_song(table, "even flow", "pearl jam");
  add_song(table, "yellow ledbetter", "pearl jam");
  add_song(table, "time", "pink floyd");
  print_library(table);
  printf("====================================\n\n");
  
  printf("Testing print_artist\n");
  print_artist(table, "pearl jam");
  printf("\n");
  print_artist(table, "ac/dc");
  printf("\n");
  print_artist(table, "Bink Bloyd");
  printf("====================================\n\n");

  printf("Testing shuffle\n");
  shuffle(table, 3);
  printf("====================================\n\n");
  clear(table);
  
  return 0;
}
