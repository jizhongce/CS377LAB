#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "part2.h"



int inode_used(int input){
  return 127+48*input;
}
void ls(){
  int fd = open("file",O_RDONLY);

  int size = 0;
  char buf[1024];
  read(fd,buf,1024);
  int location = 128;
    for (int i = 1; i <=16; i++){
      char name[8];
      int x = inode_used(i);
      //find one available
      if(buf[x]==1){

        int name_index = x-47;
        //write name
        for (int i = 0; i < 8; ++i)
        {
          name[i] = buf[name_index+i];
        }
        printf("Name: %s ", name);
        //write size
        int size_index = name_index+11;
        size =  buf[size_index];
        printf("Size: %i\n", size);
      }
    }


  close(fd);
}



void f_create(char name[8], int size){

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

  int fd = open("file",O_RDWR);
  lseek(fd,0,SEEK_SET);
  char f[1024];
  read(fd,f,1024);

  for (int i = 0; i < 16; i++)
  {
    char namex[8];
    int current_location = 128+(i*48);

    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }

    // lseek(fd,128+(i*48),SEEK_SET);
    if(strcmp(namex,name)==0){
      // lseek(fd,7+(blockNum*4),SEEK_CUR);
      // int x[1];
      // read(fd,x,1);
      char pointer[8];
      int tmp = current_location+15;
      for (int k = 0; k < 8; ++k)
      {
        pointer[k] = f[tmp+4*k];
      }

      for (int z = 0; z < 48; ++z)
      {
        f[current_location+z] = 0;
      }

      for (int x = 0; x < 8; ++x)
      {
        if(pointer[x] == 0)
            continue;
        f[pointer[x]] = 0;
      }
      lseek(fd,0,SEEK_SET);
      if(!write(fd,f,1024));
      break;
    }
  }

  close(fd);
}

void f_read(char name[8], int blockNum, char buf[1024]){
   int fd = open("file",O_RDWR);
  for (int i = 0; i < 16; i++)
  {
    lseek(fd,0,SEEK_SET);
    char f[1024];
    read(fd,f,1024);
    char namex[8];
    int current_location = 128+(i*48);

    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }

    // lseek(fd,128+(i*48),SEEK_SET);
    if(strcmp(namex,name)==0){
      // lseek(fd,7+(blockNum*4),SEEK_CUR);
      // int x[1];
      // read(fd,x,1);
      int x = f[current_location+11];
      printf("%i\n", x);
      lseek(fd,1024*(x),SEEK_SET);
      read(fd,buf,1024);
    }
  }
  close(fd);
}

void f_write(char name[8], int blockNum, char buf[1024]){
   int fd = open("file",O_RDWR);
  for (int i = 0; i < 16; i++)
  {
    lseek(fd,0,SEEK_SET);
    char f[1024];
    read(fd,f,1024);
    char namex[8];
    int current_location = 128+(i*48);

    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }

    // lseek(fd,128+(i*48),SEEK_SET);
    if(strcmp(namex,name)==0){
      // lseek(fd,7+(blockNum*4),SEEK_CUR);
      // int x[1];
      // read(fd,x,1);
      int x = f[current_location+11];
      printf("%i\n", x);
      lseek(fd,1024*(x),SEEK_SET);
      write(fd,buf,1024);
    }
  }
  close(fd);
}