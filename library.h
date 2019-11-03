struct song_node * table[27];

struct song_node * add_song(struct song_node ** library, char * name, char * artist);
struct song_node * search_song(struct song_node ** library, char * name, char * artist);
void print_letter(struct song_node ** library, char letter);
void print_artist(struct song_node ** library, char * artist);
void print_library(struct song_node ** library);
void shuffle(struct song_node ** library);
void delete(struct song_node ** library, char * name, char * artist);
void clear(struct song_node ** library);
