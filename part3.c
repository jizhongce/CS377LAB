#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
  char buffer[1000];
  char bin[1000] = "/bin/";

  while (1) {
    printf("batch-shell> ");
    fgets(buffer,1000,stdin);

    //split commands
    char* token;
    char* temp[1000];
    char tmp[2] = " ";
    int count = 0;
    token = strtok(buffer,tmp);
    while (token!=NULL) {
      temp[count] = token;
      count++;
      // printf("%s\n", token);
      token = strtok(NULL,tmp);
    }

    int result = 0;


    if(strcmp("quit",temp[0]) == 0){
      exit(0);
    }

    for(int i=0; i<count; i++){
      if(fork()==0){
        strcat(bin,temp[i]);
        strtok(bin,"\n");
        execl(bin,buffer,NULL);
        // system(temp[i]);
      }
      waitpid(-1,NULL,0);
    }

    continue;
  }

  return 0;
}
