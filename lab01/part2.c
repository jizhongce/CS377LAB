#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int main(){

  int input1;

  printf("Please enter process ID\n");
  //get the user input
  scanf("%d",&input1);

  //kill the input process
  kill(input1,SIGKILL);

  //handle errors
  switch (errno) {
    case EINVAL: printf("The value is not correct\n");
      break;
    case ESRCH: printf("No such a process\n");
      break;
    case EPERM: printf("Operation not permitted\n");
      break;
    default: printf("SUCCESS\n");
  }

}
