#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/shm.h>


int main(int argc, char **argv) {

    pid_t pid[4];                                                                          //variable to hold id
    int fd[2];                                                                          //variable to hold pipe
    int shm_id[4];
    int *shm_ptr;
    int waitStatus;

  for(int i = 0; i < 4; i++) {                                                        //loop to create 4 processes
    if(pipe(fd) == -1) {                                                              //calling pipe here, and checking if it failed
        printf("Pipe has failed\n");
        return 1;
    }
    shm_id[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);                    //creating shared id
    if(shm_id[i] < 0) {                                                                //checking if failed
        printf("shmget has failed\n");
        return 1;
    }
    shm_ptr = (int*) shmat(shm_id[i], NULL, 0);                                        //getting pointer to a shm_id
    if((long)shm_ptr == -1) {                                                          //checking if the cmd to pointer failed
        printf("shmat has failed\n");
        return -1;
      }
    pid[i] = fork();                                                                     //calling fork here
    if(pid[i] == -1) {                                                                   //if fork has failed
      printf("fork has failed\n");
      return 1;
    }
    else if(pid[i] > 0) {                                                                    //in the parent
      close(fd[0]);                                                                         //closing reading end of pipe
      write(fd[1], &shm_id[i], sizeof(int));
      close(fd[1]);                                                                         //closing writing end of pipe
      printf("Coordinator: forked process with ID %d.\n", pid[i]);
      printf("Coordinator: wrote shm ID %d to pipe (4 bytes)\n", shm_id[i]);
    }
    else if(pid[i] == 0) {                                                               //In the child
      close(fd[1]);                                                                      //closing writing end of pipe
      char str[sizeof(fd[0])];
      sprintf(str, "%d", fd[0]);
      execlp("./Checker", "Checker.o", argv[1], argv[i+2], str, NULL);              //call execlp with checker, and three arguements
      printf("execlp was not sucessful\n");                                           //if execlp was not successful print;
      exit(0);                                                                        //exiting the child process
    }
  }
  for(int i = 0; i < 4; i++) {                                                        //loop to wait for each processes
    printf("Coordinator: waiting on child process ID [%d]. . .\n", pid[i]);
    wait(&waitStatus);                                                                //waiting
    shm_ptr = (int*) shmat(shm_id[i], NULL, 0);                                       //getting the pointer to a specific shared id
    if((long)shm_ptr == -1) {                                                         //checking if the cmd to pointer failed
        printf("shmat has failed\n");
        return -1;
      }
      if(*shm_ptr == 1) {                                                               //printing the results from shm_pointer
        printf("Coordinator: result %d read from shared memory: %s is divisible by %s.\n", *shm_ptr, argv[i+2], argv[1]);
      }
      if(*shm_ptr == 0) {
        printf("Coordinator: result %d read from shared memory: %s is not divisible by %s.\n", *shm_ptr, argv[i+2], argv[1]);
      }
  }
  if(shmdt(shm_ptr)) {                            //deattachin the shared pointer
      printf("shmdt has failed\n");
      return 1;
  }
  // else{
  //   printf("shmdt has worked\n");
  // }
  for(int i = 0; i < 4; i++) {                //deleting shared id's
    if(shmctl(shm_id[i], IPC_RMID, 0) < 0) {
        printf("shmctl has failed\n");
        return 1;
    }
    // else{
    //   printf("shmctl has worked\n");
    // }
  }
  printf("Coordinator: exiting.\n");
  return 0;
}
