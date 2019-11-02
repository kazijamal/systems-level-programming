#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songnode.h"

void print_list(struct song_node * list) {
  printf("[ ");
  while (list != NULL) {
    printf("%s : %s, ", list->artist, list->name);
    list = list->next;
  }
  printf("]\n");
}

//based on artist and song name
struct song_node * find_song(struct song_node * list, char name[100], char artist[100]) {

	while (list != NULL) {

		if (strcmp(list->artist,artist) > 0) {
			//artist wont be in list because alphabetical
			return NULL;
		}

		else if (strcmp(list->artist,artist) == 0 && strcmp(list->name,name) > 0) {
			//name wont be in list because alphabetical
			return NULL;
		}

		else if (strcmp(list->artist,artist) == 0 && strcmp(list->name,name) == 0) {
			return list;
		}

		list = list->next;
	}

	//returns NULL because not found
	return list;
}

//first song, based on artist
struct song_node * find_artist_first(struct song_node * list, char artist[100]) {

	while (list != NULL) {
		
		if (strcmp(list->artist,artist) > 0) {			
			//wont be in list because alphabetical
			return NULL;
		}

		else if (strcmp(list->artist,artist) == 0) {
			return list;
		}

		list = list->next;
	}

	//returns NULL because not found
	return list;
}

//assuming don't remove from beginning
void * remove_node(struct song_node * list, char * name, char * artist) {

	struct song_node * curr = list->next;
	struct song_node * prev = list;

	while (curr != NULL) {

		if (strcmp(curr->name,name) == 0 && strcmp(curr->artist,artist) == 0) {

			prev->next = curr->next;
			free(curr);
		}	

		prev = curr;
		curr = curr->next;
	}
}

struct song_node * free_list(struct song_node * list) {

	struct song_node * next;

    while (list != NULL) {

        next = list->next;
        printf("freeing node: %s:%s\n",list->artist,list->name);
        free(list);
        list = next;
    }

    return list;
}

struct song_node * insert_front(struct song_node * list, char name[100], char artist[100]) {
  struct song_node *new = malloc(sizeof(struct song_node));
  strcpy(new->name, name);
  strcpy(new->artist, artist);
  new->next = list;
  return new;
}

struct song_node * insert_ordered(struct song_node * list, char name1[100], char artist1[100]) {

  //create new song_node
  struct song_node *new = malloc(sizeof(struct song_node));
  strcpy(new->name, name1);
  strcpy(new->artist, artist1);

  //insert front case 1 (null list)
  if (list == NULL) {
  	new->next = NULL;
  	list = new;
	return list;
  }

  //insert front case 2 (artist greater)
  if (strcmp(list->artist,artist1) > 0) {
	new->next = list;
    return new;
  }

  //insert front case 3 (artist same, name greater)
  else if (strcmp(list->artist,artist1) == 0 && strcmp(list->name,name1) > 0) {
	new->next = list;
    return new;
  }

  //create pointers to go through list
  struct song_node *curr = list->next;
  struct song_node *prev = list;

  //go through list
  while (curr != NULL) {

	//find bigger artist string
    if(strcmp(curr->artist,artist1) > 0) {
		new->next = curr;
		prev->next = new;
		return list;
	}

	//find same artist string
	else if (strcmp(curr->artist,artist1) == 0) {

		//find bigger name string
		if (strcmp(curr->name,name1) > 0) {
			new->next = curr;
			prev->next = new;
			return list;
		}
	}

	//find neither, keep going
	prev = curr;
	curr = curr->next;
  }

  //end of list
  prev->next = new;
  new->next = NULL;

  return list;
}
