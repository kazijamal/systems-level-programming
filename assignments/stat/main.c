#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>

struct stat file;

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

int main() {
  char * file_name = "main.c";
  stat(file_name, &file);

  printf("Displaying metadata of file %s\n\n", file_name);

  long file_size = file.st_size;
  printf("File size in bytes: %ld\n", file_size);

  mode_t file_mode = file.st_mode;
  printf("Mode (permissions): %o\n", file_mode);

  time_t atime = file.st_atime;
  printf("Time of last access: %s", ctime(&atime));

  float float_file_size = (float) file_size;
  while (float_file_size >= 1024) float_file_size /= 1024;
  char str_file_size[100];
  sprintf(str_file_size, "%.2f %s", float_file_size, readable_size(file_size));
  printf("Size in human readable form = %s\n", str_file_size);

  char formatted_mode[10];
  permissions(file_mode, formatted_mode);
  printf("Permissions in ls -l form: %s\n", formatted_mode);

  return 0;
}
