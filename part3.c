#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  // char input[1024];
  char buffer[1024];

  while (1) {
    printf("batch-shell> ");
    fgets(buffer,1024,stdin);
    execvp("ls",(char*)0);
  }

  return 0;
}
