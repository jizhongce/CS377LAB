#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "part2.h"


int main(){
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
