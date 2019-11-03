# mks65-project0_myTunes
Kazi Jamal and Michael Robertson

You may work with up to 1 other person, and that is highly encouraged.

Write a program in C that implements a music library organizer. The data structure should consist of an array of 27 slots (one for each letter from 'a' to 'z', and another for other symbols). Each slot will contain a linked list of all the artists that have names that start with the corresponding letter. When you add a song, it should go on to a linked list at the appropriate array slot in the correct position alphabetically. Assume no duplicate songs.

Your nodes/links should be able to hold a song's title and artist. You might use structures like the following:
```c
struct song_node{ 
  char name[100];
  char artist[100];
  struct song_node *next;
};


//and later:

struct song_node * table[27];
```

You should start by making your linked lists work with the following functionality:
- insert nodes at the front
- insert nodes in order
- alphabetical by Artist then by Song
- print the entire list
- find and return a pointer to a node based on artist and song name
- find and return a pointer to the first song of an artist based on artist name
- Return a pointer to random element in the list.
- remove a single specified node from the list
- free the entire list

DO NOT WORK ON THIS PART UNTIL YOUR LINKED LIST IS COMPLETE
Then create your array of linked lists for the full program to have the following functions:
- Add song nodes.
- Search for a song given song and artist name (return a pointer).
- Search for an artist.
- Print out all the entries under a certain letter.
- Print out all the songs of a certain artist
- Print out the entire library.
- Shuffle - print out a series of randomly chosen songs.
- Delete a song
- Clear the library.

Files you should have:
- A .c file that contains the main function you use to test all your work
- Two sets of .h/.c files
  - There are 2 separate structures being worked on, the linked list and the library.
- A makefile that will compile all the parts of your code and generate a single executable program

Git clone link:
https://github.com/mks65/my_tunes.git

You must test all the functions in your main function in order to receive full credit!!!

Example of reasonable testing output:
```
LINKED LIST TESTS
====================================

Testing print_list:
 ac/dc: thunderstruck | pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
====================================

Testing print_node:
 ac/dc: thunderstruck
====================================

Testing find_node:
looking for [pearl jam: even flow]
 node found! pearl jam: even flow
looking for [pearl jam: daughter]
 node not found
====================================

Testing find_artist:
looking for [pink floyd]
 artist found! pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
looking for [pearl jam]
 artist found! pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
looking for [presidents of the united states of america]
 artist not found
====================================

Testing songcmp (helper function):
Comparing [pearl jam: even flow] to [pearl jam: even flow]
 0
Comparing [pearl jam: even flow] to [pearl jam: alive]
 4
Comparing [pearl jam: alive] to [pearl jam: even flow]
 -4
Comparing [pearl jam: even flow] to [pink floyd: time]
 -4
====================================

Testing random:
radiohead: paranoid android
radiohead: street spirit (fade out)
radiohead: street spirit (fade out)
radiohead: paranoid android
====================================

Testing remove:
Removing [pearl jam: alive]
 ac/dc: thunderstruck | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
Removing [pearl jam: yellow ledbetter]
 ac/dc: thunderstruck | pearl jam: even flow | pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
Removing [pink floyd: alive]
 pearl jam - alive not found
ac/dc: thunderstruck | pearl jam: even flow | pink floyd: time | radiohead: paranoid android | radiohead: street spirit (fade out) | 
====================================

Testing free_list
freeing node: ac/dc - thunderstruck
freeing node: pearl jam - even flow
freeing node: pink floyd - time
freeing node: radiohead - paranoid android
freeing node: radiohead - street spirit (fade out)
list after free_list:

====================================

MUSIC LIBRARY TESTS

====================================

Testing print_library
a list
 ac/dc: thunderstruck | 
p list
 pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | presidents of the united states of america: peaches | 
r list
 radiohead: paranoid android | radiohead: street spirit (fade out) | 
====================================

Testing print_letter
p list
 pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | presidents of the united states of america: peaches | 
====================================

Testing find:
looking for [pearl jam: alive]
 song found! pearl jam: alive
looking for [pearl jam: time]
 song not found
====================================

Testing find artist:
looking for [pearl jam]
 artist found! pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | presidents of the united states of america: peaches | 
looking for [pink floyd]
 artist found! pink floyd: time | presidents of the united states of america: peaches | 
looking for [bob dylan]
 artist not found
====================================

Testing remove_song
removing: [pearl jam: alive]
a list
 ac/dc: thunderstruck | 
p list
 pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | presidents of the united states of america: peaches | 
r list
 radiohead: paranoid android | radiohead: street spirit (fade out) | 

removing: [pearl jam: yellow ledbetter]
a list
 ac/dc: thunderstruck | 
p list
 pearl jam: even flow | pink floyd: time | presidents of the united states of america: peaches | 
r list
 radiohead: paranoid android | radiohead: street spirit (fade out) | 
====================================

Testing clear_library:
freeing node: ac/dc - thunderstruck
freeing node: pearl jam - even flow
freeing node: pink floyd - time
freeing node: presidents of the united states of america - peaches
freeing node: radiohead - paranoid android
freeing node: radiohead - street spirit (fade out)

Library after clear:
====================================

Adding songs to empty library
a list
 ac/dc: thunderstruck | 
p list
 pearl jam: alive | pearl jam: even flow | pearl jam: yellow ledbetter | pink floyd: time | 
====================================

Testing print_artist:
Printing [pearl jam]
[pearl jam: alive]
[pearl jam: even flow]
[pearl jam: yellow ledbetter]

Printing [ac/dc]
[ac/dc: thunderstruck]
====================================

Testing shuffle
ac/dc: thunderstruck
ac/dc: thunderstruck
pearl jam: yellow ledbetter
====================================
```