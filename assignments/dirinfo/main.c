#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

char * readable_size(long size) {
  char * units[] = {"B", "KB", "MB", "GB"};
  int i = 0;
  while (size >= 1024) {
    size /= 1024;
    i++;
  }
  return units[i];
}

void permissions(mode_t mode, char * ans) {
  char rwx[] = "rwxrwxrwx";
  int i;
  for (i = 1; i <= 9; i++) {
    if (!(mode & (1 << (9 - i)))) rwx[i-1] = '-';
  }
  strcpy(ans, rwx);
}

void ls_format(char * path, char * d_name, char * ans) {
  struct stat file;
  char currPath[256];
  strcpy(currPath, path);
  strcat(currPath, d_name);
  stat(currPath, &file);
  char formatted_mode[10];
  permissions(file.st_mode, formatted_mode);
  char * formatted_atime = ctime(&(file.st_atime));
  formatted_atime[strlen(formatted_atime)-1] = '\0';
  char formatted[256];
  sprintf(formatted, "%s %ld %s\t %s\t %ld\t %s\t %s\t", formatted_mode, file.st_nlink, getpwuid(file.st_uid)->pw_name, getgrgid(file.st_gid)->gr_name, file.st_size, formatted_atime, d_name);
  strcpy(ans, formatted);
}

int main(int argc, char *argv[]) {

  char dir_name[256];

  // takes directory name from command line input if given
  if (argc > 1) {
    strcpy(dir_name, argv[1]);
  }
  // asks user for directory if not given as command line input
  else {
    printf("Enter a directory to scan: ");
    fgets(dir_name, 256, stdin);
    int i = 0;
    while (dir_name[i] != '\n') {
      i++;
    }
    dir_name[i] = '\0';
  }

  // creates path for nested directories
  DIR * dir = opendir(dir_name);

  while (dir == NULL) {
    printf("Opening directory %s... %s\n", dir_name, strerror(errno));
    printf("\nEnter a directory to scan: ");
    dir_name[0] = '\0';
    fgets(dir_name, 256, stdin);
    int i = 0;
    while (dir_name[i] != '\n') {
      i++;
    }
    dir_name[i] = '\0';
    dir = opendir(dir_name);
  }
  
  char path[256];
  strcpy(path, dir_name);
  strcat(path, "/");
  
  struct dirent * curr = readdir(dir);

  printf("Statistics for directory: %s\n", dir_name);
  
  // show the total size of all the regular files in the directory

  long dir_size = 0;
  struct stat file;

  while (curr != NULL) {
    if (curr->d_type == DT_REG) {
      char currPath[256];
      strcpy(currPath, path);
      strcat(currPath, curr->d_name);
      stat(currPath, &file);
      dir_size += file.st_size;
    }
    curr = readdir(dir);
  }

  // print out the size in a more readable format
  
  float float_dir_size = (float) dir_size;
  while (float_dir_size >= 1024) float_dir_size /= 1024;
  char readable_dir_size[100];
  sprintf(readable_dir_size, "%.2f %s", float_dir_size, readable_size(dir_size));
 
  printf("Total Directory Size: %ld Bytes or %s\n", dir_size, readable_dir_size);

  // specify which files are directories (if any)

  printf("\nDirectories:\n");

  rewinddir(dir);
  curr = readdir(dir);

  while (curr != NULL) {
    if (curr->d_type == DT_DIR) {
      printf("\t%s\n", curr->d_name);
    }
    curr = readdir(dir);
  }
    
  // list all the files in the directory

  printf("\nRegular files:\n");

  rewinddir(dir);
  curr = readdir(dir);

  while (curr != NULL) {
    if (curr->d_type == DT_REG) {
      printf("\t%s\n", curr->d_name);
    }
    curr = readdir(dir);
  }

  // make it look more like $ ls -l

  printf("\nls -l\n");
  
  rewinddir(dir);
  curr = readdir(dir);

  while (curr != NULL) {
    if (curr->d_type == DT_DIR) {
      char ls_formatted[256];
      ls_format(path, curr->d_name, ls_formatted);
      printf("%s\n", ls_formatted);
    }
    curr = readdir(dir);
  }

  rewinddir(dir);
  curr = readdir(dir);

  while (curr != NULL) {
    if (curr->d_type == DT_REG) {
      char ls_formatted[256];
      ls_format(path, curr->d_name, ls_formatted);
      printf("%s\n", ls_formatted);
    }
    curr = readdir(dir);
  }

  closedir(dir);
  
  return 0;
}
