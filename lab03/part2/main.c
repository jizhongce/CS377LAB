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
  f_write("aaaaaaa",2,buf);
  char y[1024];
  f_read("aaaaaaa",2,y);
  int count=0;
  for (int i = 0; i < 1024; ++i)
  {

    /* code */
    count++;
    printf("%i: %c\n", count, y[i]);
  }


  free(x);
  // printf("%i\n", strcmp("helloo.c","helloo.c"));
}
