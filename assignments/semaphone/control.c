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

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int create_sem() {
  int semd;
  int v, r;
  char input[3];

  semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(SEM_KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0);
    printf("semaphore created\n");
  }
  else {
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
    printf("semaphore created\n");
  }

  return semd;
}

int remove_sem(int semd) {
  semctl(semd, IPC_RMID, 0);
  printf("semaphore removed\n");
  return 0;
}

int create_shm() {
  int shmd;
  shmd = shmget(SHM_KEY, SEG_SIZE, IPC_CREAT | 0644);
  printf("shared memory created\n");
  return shmd;
}

int remove_shm(int shmd) {
  shmctl(shmd, IPC_RMID, 0);
  printf("shared memory removed\n");
  return 0;
}

int create_file(char * filename) {
  int fd;
  fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0644);
  if (fd == -1) {
    fd = open(filename, O_RDWR | O_TRUNC, 0644);
  }
  printf("file created\n");
  return fd;
}

int remove_file(char * filename) {
  remove(filename);
  printf("file removed\n");
  return 0;
}
  

int main(int argc, char *argv[]) {
  int semd;
  int shmd;
  int fd;
  char * filename = "story";
  // no command line argument
  if (argc == 1) {
    printf("provide command line argument -c to create, -r to remove, or -v to view\n");
    return 0;
  }
  // -c create
  if (strcmp(argv[1], "-c") == 0) {
    semd = create_sem();
    shmd = create_shm();
    fd = create_file(filename);
  }
  // -r remove
  else if (strcmp(argv[1], "-r") == 0) {
    struct sembuf buff;
    buff.sem_num = 0;
    buff.sem_op = -1;
    printf("trying to get in\n");
    semop(semd, &buff, 1);
    printf("The story so far:\n");
    fd = open(filename, O_RDONLY);
    char reading[SEG_SIZE];
    while(read(fd, reading, SEG_SIZE) > 0) {
        printf("%s\n", reading);
    }
    printf("\n");
    semd = semget(SEM_KEY, 1, 0);
    shmd = shmget(SHM_KEY, SEG_SIZE, 0600);
    remove_shm(shmd);
    remove_file(filename);
    remove_sem(semd);
  }
  // -v view
  else if (strcmp(argv[1], "-v") == 0) {
    fd = open(filename, O_RDONLY);
    printf("The story so far:\n");
    char reading[SEG_SIZE];
    while(read(fd, reading, SEG_SIZE) > 0) {
        printf("%s\n", reading);
    }
    close(fd);
  }
  return 0;
}
