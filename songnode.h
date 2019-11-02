struct song_node {
  char name[100];
  char artist[100];
  struct song_node * next;
};

void print_list(struct song_node * list);
struct song_node * insert_front(struct song_node * list, char * name, char * artist);
struct song_node * insert_ordered(struct song_node * list, char * name, char * artist);
struct song_node * find_song(struct song_node * list, char * name, char * artist);
struct song_node * find_artist_first(struct song_node * list, char * artist);
struct song_node * rand_node(struct song_node * list);
struct song_node * remove_node(struct song_node * list, char * name, char * artist);
struct song_node * free_list(struct song_node * list);
