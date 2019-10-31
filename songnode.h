struct song_node {
  char name[100];
  char artist[100];
  struct song_node *next;
};

struct song_node * insert_front(struct node * list, char * name, char * artist);
struct song_node * insert_ordered(struct node * list, char * name, char * artist);
void print_list(struct node * list);
struct song_node * find_song(struct node * list, char * name, char * artist);
struct song_node * find_arist_first(struct node * list, char * artist);
struct song_node * rand_node(struct node * list);
void * remove_node(struct node * list, char * name, char * artist);
struct song_node * free_list(struct node * list);
