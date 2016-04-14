#include <stdio.h>
#include <stdlib.h>
#include "part2.h"


void ls(){

}

int create(char name[8], int size){

  FILE *fp = fopen("file_system","r+b");
  int pointer[8];
  //write to free block list
  int b1;
  int b2;
  int count = size;
  int num=0;
  int index=0;
  while (1) {
    if (count==0) {
      break;
    }
    //get the byte
    b1=fgetc(fp);
    if(b1==' '||b1=='\n')
      continue;
    b2=fgetc(fp);

    num++;

    if(b2=='1')
      continue;
    else{
      pointer[index] = num;
      index++;
      fseek(fp, -1, SEEK_CUR);
      fputc('1',fp);
      fseek(fp, 0, SEEK_CUR);
      count--;
      continue;
    } 
  }













    fclose(fp);
}

int delete(char name[8]){
  return 1;
}

int read(char name[8], int blockNum, char buf[1024]){
  return 1;
}

int write(char name[8], int blockNum, char buf[1024]){
  return 1;
}
