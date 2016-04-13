#include "stdio.h"
#include "stdlib.h"



int main(){

  FILE *fp = fopen("data/input.txt","r");

  unsigned int offset_num;
  unsigned int page_num;

  fscanf(fp,"%i",&offset_num);
  fscanf(fp,"%i",&page_num);

  unsigned int offset_mask = (1<<offset_num)-1;
  unsigned int page_mask = ((1<<page_num)-1)<<offset_num;

  unsigned int tmp;
  int count = 1;
  
  while (fscanf(fp,"%i",&tmp)!=-1) {
    unsigned int offset = tmp & offset_mask;
    unsigned int page = tmp & page_mask;
    printf("virtual address v%i is in page number %u and offset %u.\n", count,page,offset);
    count++;
  }




  fclose(fp);

}
