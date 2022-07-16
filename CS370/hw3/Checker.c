#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

 int main(int argc, char **argv) {
  printf("Checker process [%d]: Starting.\n", getpid());

  int divide = atoi(argv[1]);                                  //converting from char to int
  int divisible = atoi(argv[2]);                               //converting from char to int
  int fd;
  int shm_id;
  fd = atoi(argv[3]);                                         //getting the pipe
  read(fd, &shm_id, sizeof(int));                             //reading from the pipe
  printf("Checker process [%d]: read 4 bytes containing shm ID %d\n", getpid(), shm_id);
  int *shm_ptr = (int*) shmat(shm_id, NULL, 0);                       //getting the pointer to a shm_id
  if((long)shm_ptr == -1) {                                           //checking if shmat failed
      printf("shmat has failed\n");
      return 1;
  }
  if(divisible % divide == 0) {                                                   //checking if divisible
    printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), divisible, divide);
    printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
    *shm_ptr = 1;                                                                 //assigning shm_ptr with 1
    exit(1);                                                                      //return 1
  }
  else {                                                                           //if not divisible
    printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), divisible, divide);
    printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
    *shm_ptr = 0;                                                                 //assigning shm_ptr with 0
    exit(0);                                                                        //return 0
  }
}
