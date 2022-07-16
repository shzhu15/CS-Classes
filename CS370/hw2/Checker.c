#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/types.h>

 int main(int argc, char **argv) {
  long divide = strtol(argv[1], NULL, 10);                                  //converting from char to int
  long divisible = strtol(argv[2], NULL, 10);                               //converting from char to int

  printf("Checker process [%d]: Starting.\n", getpid());
  if(divisible % divide == 0) {                                                   //checking if divisible
    printf("Checker process [%d]: %ld *IS* divisible by %ld.\n", getpid(), divisible, divide);
    printf("Checker process [%d]: Returning 1.\n", getpid());
    exit(1);                                                                      //return 1
  }
  else {                                                                           //if not divisible
    printf("Checker process [%d]: %ld *IS NOT* divisible by %ld.\n", getpid(), divisible, divide);
    printf("Checker process [%d]: Returning 0.\n", getpid());
    exit(0);                                                                        //return 0
  }
}
