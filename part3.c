#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
  //create buffer to store user input
  char buffer[1000];
  //path
  char bin[1000] = "/bin/";

  //outer while loop
  while (1) {
    printf("batch-shell> ");
    fgets(buffer,1000,stdin);

    //split commands

    //buffer for single command
    char* token;
    //array of commands
    char* temp[1000];
    char tmp[2] = " ";
    int count = 0;

    //split user input by space " "
    token = strtok(buffer,tmp);
    while (token!=NULL) {
      temp[count] = token;
      //increment count
      count++;
      token = strtok(NULL,tmp);
    }

    //if user enter "quit", exit program
    if(strcmp("quit",temp[0]) == 0){
      exit(0);
    }


    //execute each command
    for(int i=0; i<count; i++){
      //if it's child
      if(fork()==0){
        //get command
        strcat(bin,temp[i]);
        //we eliminate the "\n" at the end
        strtok(bin,"\n");
        //execute the command
        execl(bin,buffer,NULL);
      }
      // wait all children
      waitpid(-1,NULL,0);
    }
    //continue the while loop
    continue;
  }

  return 0;
}
