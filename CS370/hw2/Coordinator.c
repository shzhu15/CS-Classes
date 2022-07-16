#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/types.h>


int main(int argc, char **argv) {
  pid_t pid;
  for(int i = 0; i < 4; i++) {                                                        //loop to create 4 processes
    pid = fork();                                                                     //calling fork here
    int waitStatus;

    if(pid == -1) {                                                                   //if fork has failed
      printf("fork has failed\n");
      return -1;
    }
    else if(pid > 0) {                                                                           //in the parent
      printf("Coordinator: forked process with ID %d.\n", pid);
      printf("Coordinator: waiting for process [%d].\n", pid);
      wait(&waitStatus);                                                                        //waiting for child
      printf("Coordinator: child process %d returned %d.\n", pid, WEXITSTATUS(waitStatus));

    }
    else if(pid == 0) {                                                               //In the child
      execlp("./Checker", "Checker.o", argv[1], argv[i+2], NULL);                     //call execlp with checker, and two arguements
      printf("execlp was not sucessful\n");                                           //if execlp was not successful print;
      exit(0);                                                                        //exiting the child process
    }
  }
  printf("Coordinator: exiting.\n");
  return 0;
}
