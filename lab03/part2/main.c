#include "stdio.h"
#include "stdlib.h"
#include "part2.h"


int main(){
  char* x = (char*)malloc(8*sizeof(char));
  for (int i = 0; i < 7; ++i)
  {
    x[i] = 'a';
  }
  f_create(x,3);
  f_create("helloo.c",5);
  free(x);

}
