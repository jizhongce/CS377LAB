#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "part2.h"


int main(){

  FILE *fp = fopen("data/input.txt","r");

  char name;
  fscanf(fp,"%s",&name);


  //create disk
  printf("%s\n",&name);
  char command[90];
  strcpy(command, "./create ");
  strcat(command,&name);
  system(command);


  char type[2];

  while (fscanf(fp,"%s",type)!=-1) {
      printf("%s\n", type);
    if(strcmp(type,"C")==0){
      char name[8];
      int size;
      fscanf(fp,"%s",name);
      printf("%s\n", name);
      fscanf(fp,"%i",&size);
      printf("%i\n", size);
    }
    // else if(strcmp(type,"L")){
    //   printf("L\n");
    //   continue;
    // }
    // else if(strcmp(type,"W")){
    //   char *name;
    //   int size;

    //   fscanf(fp,"%s",name);
    //   fscanf(fp,"%i",&size);
    //   printf("%s\n", name);
    //   printf("%i\n", size);
    //   continue;
    // }
    // else if(strcmp(type,"D")){
    //   char *name;

    //   fscanf(fp,"%s",name);
    //   printf("%s\n", name);
    //  continue;
    // }
    // else{
    //   char *name;
    //   int size;

    //   fscanf(fp,"%s",name);
    //   fscanf(fp,"%i",&size);
    //   printf("%s\n", name);
    //   printf("%i\n", size);
    //   continue;
    // }

  }

  fclose(fp);

}
