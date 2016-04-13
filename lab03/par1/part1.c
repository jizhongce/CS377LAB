#include "stdio.h"
#include "stdlib.h"



int main(){

  FILE *fp = fopen("data/input.txt","r");
  unsigned int lowest;
  fscanf(fp,"%i",&lowest);
  printf("%u\n",lowest);

}
