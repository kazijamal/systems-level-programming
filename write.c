#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

#define SEM_KEY 24602
#define SHM_KEY 24601
#define SEG_SIZE 200

int main() {
  char * filename = "story";
  int semd = semget(SEM_KEY, 1, 0);
  struct sembuf buff;
  buff.sem_num = 0;
  buff.sem_op = -1;
  printf("trying to get in\n");
  semop(semd, &buff, 1);
  int shmd;
  shmd = shmget(SHM_KEY, SEG_SIZE, 0600);
  if(shmd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return 1;
  }
  char * last;
  last = shmat(shmd, 0, 0);
  printf("Last addition: %s\n", last);
  printf("Your addition: ");
  fgets(data, SEG_SIZE, stdin);
  *strchr(data, '\n') = 0;
  int fd = open(filename, O_WRONLY | O_APPEND);
  write(fd, data, SEG_SIZE);
  close(fd);
  shmdt(data);
  buff.sem_op = 1;
  semop(semd, &buff, 1); 
  return 0;
}
