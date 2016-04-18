#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "part2.h"


void ls(){

}


int inode_used(int input){
  return 127+48*input;
}


int f_create(char name[8], int size){

    char sizex = (char)size;
    int fd;
    char *buf;
    int* block_pointer= (int*)malloc(8*sizeof(int));

    buf = (char *) calloc(1024,sizeof(char));

    fd = open("file",O_RDWR);

    //read 1024 bytes 
    if(read(fd,buf,1024)<0){
      printf("error: read failed\n");
    }

    //return to the beginning of file
    lseek(fd,0,SEEK_SET);
    int count = 1;
    int count2 = 0;
    // write to free block list
    while(size>0 && count<127){
      if(buf[count]== 0){
        buf[count] = 1;
        block_pointer[count2] = count;
        count2++;
        size--;
      }
      count++;
    }

    //write to inode
    for (int i = 1; i <=16; i++){
      int x = inode_used(i);
      //find one available
      if(buf[x]==0){
        buf[x] =1;
        int name_index = x-47;
        //write name
        for (int i = 0; i < 8; ++i)
        {
          buf[name_index+i] = name[i];
        }
        //write size
        int size_index = name_index+11;
        buf[size_index] = sizex;

        //write block pointer
        for (int i = 0; i < 8; ++i)
        {
          buf[size_index+4*(i+1)] = block_pointer[i];
        }
        break;
      }
    }

    if(write(fd,buf, 1024)<0)
    printf("error: write failed \n");
    close(fd);
    free(block_pointer);
    free(buf);
}

int f_delete(char name[8]){
  return 1;
}

int f_read(char name[8], int blockNum, char buf[1024]){
  return 1;
}

int f_write(char name[8], int blockNum, char buf[1024]){
  return 1;
}
