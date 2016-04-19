#include "stdio.h"
#include "stdlib.h"



int main(){

  //Open the input file
  FILE *fp = fopen("data/input.txt","r");

  unsigned int offset_num;
  unsigned int page_num;

  //Get the first line of the input file which is offset number
  fscanf(fp,"%i",&offset_num);
  //Get the second line of the input file which is page number
  fscanf(fp,"%i",&page_num);
  //Here we create a offset mask to get the offset number
  unsigned int offset_mask = (1<<offset_num)-1;
  //Here we create a page mask to get the page number
  unsigned int page_mask = ((1<<page_num)-1)<<offset_num;

  unsigned int tmp;
  int count = 1;

  //In this while loop we will read each virtual address from the input file and extract each page number and offset from the virtual address. Then print out the ouput
  while (fscanf(fp,"%i",&tmp)!=-1) {
    //get the offset of the the virtual address
    unsigned int offset = tmp & offset_mask;
    //get the page number of the virtual address
    unsigned int page = tmp & page_mask;
    //print out the output
    printf("virtual address v%i is in page number %u and offset %u.\n", count,page,offset);
    count++;
  }

  fclose(fp);

}
