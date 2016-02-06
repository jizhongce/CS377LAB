#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int main(){

  int input1;

  printf("Please enter process ID\n");
  scanf("%d",&input1);

  int a = kill(input1,SIGKILL);

  switch (errno) {
    case EINVAL: printf("The value is not correct");
      break;
    case ESRCH: printf("No such a process");
      break;
    case EPERM: printf("Operation not permitted");
      break;
    default: printf("SUCCESS");
  }
}
