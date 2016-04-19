#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "part2.h"



int main(){

  FILE *fp = fopen("data/input.txt","r");


  char buf[1024];
  for (int i=0; i<1024;i++) {
    /* code */
    buf[i] = 'b';
  }
  char disk_name;
  fscanf(fp,"%s",&disk_name);


  //create disk
  char command[90];
  strcpy(command, "./create ");
  strcat(command,&disk_name);
  system(command);


  char type[1];

  while (fscanf(fp,"%s",type)!=-1) {
      // printf("%s\n", type);s
    //create file
    if(strcmp(type,"C")==0){
      char name[8];
      int size;
      fscanf(fp,"%s",name);
      // printf("%s\n", name);
      fscanf(fp,"%i",&size);
      // printf("%i\n", size);
      f_create(name,size);
      // free(name);
    }
    //list file
    else if(strcmp(type,"L")==0){
      ls();
    }
    //write file
    else if(strcmp(type,"W")==0){
      char name[8];
      int size;
      fscanf(fp,"%s",name);
      fscanf(fp,"%i",&size);
      // printf("%s\n", name);
      // printf("%i\n", size);
      f_write(name,size,buf);
    }
    //delete file
    else if(strcmp(type,"D")==0){
      char name[8];
      fscanf(fp,"%s",name);
      // printf("%s\n", name);
      f_delete(name);
    }
    //read file
    else{
      char name[8];
      int size;
      fscanf(fp,"%s",name);
      fscanf(fp,"%i",&size);
      // printf("%s\n", name);
      // printf("%i\n", size);
      char buf2[1024];
      f_read(name,size,buf2);
    }

  }

  fclose(fp);

}
