#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "part2.h"


int main(){
  char* x = (char*)malloc(8*sizeof(char));
  for (int i = 0; i < 7; ++i)
  {
    x[i] = 'a';
  }

  char buf[1024];

  for (int i = 0; i < 1024; ++i)
  {
    buf[i] = 'b';
  }

  f_create(x,3);
  f_create("asdfgh.c",5);
  f_create("qwerta.c",8);


  f_write(x,2,buf);
  f_write("asdfgh.c",3,buf);
  f_write("qwerta.c",1,buf);

  ls();

  // f_delete(x);

  // ls();

  // f_delete("asdfgh.c");
  // f_delete("qwerta.c");


  free(x);
}
