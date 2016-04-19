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

  char *type = (char*)malloc(sizeof(char));
  char *file_name;
  int file_size;
  fscanf(fp, "%s", &type);
  fscanf(fp, "%s", &file_name);
  fscanf(fp, "%i", &file_size);

  printf("%s\n",&type);
  printf("%s\n",&file_name);
  printf("%i\n",file_size);


  fclose(fp);




































  char* x = (char*)malloc(8*sizeof(char));
  for (int i = 0; i < 8; ++i)
  {
    x[i] = 'a';
  }

  char buf[1024];

  for (int i = 0; i < 1024; ++i)
  {
    buf[i] = 'b';
  }  

  char buf2[1024];

  for (int i = 0; i < 1024; ++i)
  {
    buf2[i] = 'c';
  }

  f_create(x,3);
  f_create("zzzzzzzz",3);



  f_write(x,2,buf);
  f_write("zzzzzzzz",2,buf2);
  // f_write(x,2,buf);
 

  ls();

  f_delete("zzzzzzzz");

  char xy[1024]; 
  f_read("aaaaaaaa",7,xy);

  // for (int i = 0; i < 1024; ++i)
  // {
  //   printf("%c\n", xy[i]);
  // }

  // ls();

  // f_delete("asdfgh.c");
  // f_delete("qwerta.c");


  free(x);
}
