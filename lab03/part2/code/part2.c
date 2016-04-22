#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "part2.h"


//This is helper funtion which will return the index of used position for the i'th inode
int inode_used(int input){
  return 127+48*input;
}
//This is how we implement the ls function
void ls(){
  printf("Listing all the files ........\n");
  //first we open the file and it is read only
  int fd = open("disk0",O_RDONLY);
  //Then we define size which will be used to get the size of the file
  int size;
  //This is a buffer which have 1024 spaces, we will use this buffer to read the file
  char buf[1024];
  //This will read the first 1024 bytes which is super block from file system.
  read(fd,buf,1024);
  //Then we set the location is 128 which is the beginning of the inode.
  int location = 128;
  //Then use a for loop to check each inode
    for (int i = 1; i <=16; i++){
      //This is string to store the name of the file. Because the filename have maximum 8 characters
      //So we have a array which have 9 spaces.
      char name[9];
      //Here we use helper method to get the index of used position
      int x = inode_used(i);
      //Then we check if this inode is used or not, if it used, we can get the name and size of this inode
      if(buf[x]==1){
        //Here we get the index of the first character of the filename
        int name_index = x-47;
        //Then we write the file name into the name array.
        for (int i = 0; i < 9; ++i)
        {
          name[i] = buf[name_index+i];
        }
        //Then we print out the name of the file
        printf("Name: %s ", name);
        //Here we get the index of size
        int size_index = name_index+11;
        //Then we get the size of that file
        size =  buf[size_index];
        //print out the size of that file
        printf("Size: %i\n", size);
      }
    }

  //close file
  close(fd);
}


//This is how we implement the create function
void f_create(char name[8], int size){

    printf("creating file %s\n", name);
    //This is the size of the file we will create
    char sizex = (char)size;
    int fd;
    //This is a buffer we will used to read the file system
    char *buf = (char *) calloc(1024,sizeof(char));
    //This will be used to store the block number that the file will use
    char *block_pointer = (char*)calloc(8,sizeof(char));
    //open the file
    fd = open("disk0",O_RDWR);

    //Here we read the first 1024 byte which is block from the file system
    if(read(fd,buf,1024)<0){
      printf("error: read failed\n");
    }

    //return to the beginning of file
    lseek(fd,0,SEEK_SET);
    //This count is used to indicate the index of the freelist
    int count = 1;
    //This count is used to indicate the index of the block_pointer
    int count2 = 0;
    // write to free block list
    while(size>0 && count<127){
      if(buf[count]== 0){
        //if we find a free block, we set that block as used, and store the block number into block_pointer
        buf[count] = 1;
        block_pointer[count2] = count;
        //Increase the index of the block_pointer
        count2++;
        //decrease the size by 1
        size--;
      }
      count++;
    }

    //write to inode
    for (int i = 1; i <=16; i++){
      //First we get the used position of the inode so that we can check if the inode is used or not
      int x = inode_used(i);
      //find one available
      if(buf[x]==0){
        //we set the inode is used
        buf[x] =1;
        //Then get the index of first character of file
        int name_index = x-47;
        //write name into buffer
        for (int i = 0; i < 8; ++i)
        {
          buf[name_index+i] = name[i];
        }
        //get the index of the size
        int size_index = name_index+11;
        //write size into buffer
        buf[size_index] = sizex;

        //write block pointer by using the block_pointer
        for (int i = 0; i < 8; ++i)
        {
          buf[size_index+4*(i+1)] = block_pointer[i];
        }
        break;
      }
    }
    //Then we write the buffer back into the file system
    if(write(fd,buf, 1024)<0)
    printf("error: write failed \n");
    //free the buffer which is used to read the file
    free(buf);
    free(block_pointer);
    //close the file
    close(fd);
}

//This is how we implement the delete function
void f_delete(char name[8]){
  printf("deleting file %s\n", name);
  //open the file
  int fd = open("disk0",O_RDWR);
  //seek to the beginning of the file
  lseek(fd,0,SEEK_SET);
  //create a buffer to read the file
  char f[1024];
  //read the first 1024 bytes which is super block into the buffer
  read(fd,f,1024);
  //Then we check the each inode in the super block
  for (int i = 0; i < 16; i++)
  {
    //This array is used to store the name which is read from the inode
    char namex[9] = "";
    //This is the first character of the file name
    int current_location = 128+(i*48);
    //read the name from the inode into the namex
    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }
    //Then we compare the input name with the name read from the inode
    if(strcmp(namex,name)==0){
      //if the both name are same then we find the file we need to delete
      //first we get the block_pointer of that file
      char pointer[8];
      //this is the index of the first block number
      int tmp = current_location+15;
      //get each block number from the block_pointer
      for (int k = 0; k < 8; ++k)
      {
        pointer[k] = f[tmp+4*k];
      }
      //clear the inode by set each as 0
      for (int z = 0; z < 48; ++z)
      {
        f[current_location+z] = 0;
      }
      //Then we clear the freelist in the super block
      for (int x = 0; x < 8; ++x)
      {
        if(pointer[x] == 0)
            break;
        f[pointer[x]] = 0;
      }
      //go back to the beginning of the file
      lseek(fd,0,SEEK_SET);
      //write back the super block with new data
      if(!write(fd,f,1024));
      break;
    }
  }
  //close file
  close(fd);
}

//This is how we implement the read function
void f_read(char name[8], int blockNum, char buf[1024]){
  printf("reading file %s\n", name);
    //open the file
   int fd = open("disk0",O_RDWR);
  //Here we use for loop to check each inode to find the inode whose name is same as input name
  for (int i = 0; i < 16; i++)
  {
    //every time we go back to the beginning of the file
    lseek(fd,0,SEEK_SET);
    //create a buffer to read
    char f[1024];
    //read the first block which is super block of the file system
    read(fd,f,1024);
    //This is a array to store the name read from inode
    char namex[8];
    //This is index of the first character of the name of that inode
    int current_location = 128+(i*48);
    //Read the name from inode
    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }
    //Here we check the input name and the name that read from the inode
    if(strcmp(namex,name)==0){
      //if the name is same, we get the block that is the in position of blockNum
      int x = f[current_location+11+4*(blockNum+1)];
      if(x == 0){
        printf("invalid blockNum while reading file %s!!!\n",name);
        break;
      }
      //Then we go to the specific block that we need to read
      lseek(fd,1024*(x),SEEK_SET);
      //read the data in that block into the buf
      read(fd,buf,1024);
    }
  }
  //close the file
  close(fd);
}

//This is how we implement the wirte function
void f_write(char name[8], int blockNum, char buf[1024]){
  printf("writing file %s\n", name);
    //open the file
   int fd = open("disk0",O_RDWR);
  //Here we use for loop to check each inode to find the inode whose name is same as input name
  for (int i = 0; i < 16; i++)
  {
    //every time we go back to the beginning of the file
    lseek(fd,0,SEEK_SET);
    //create a buffer to read
    char f[1024];
    //read the first block which is super block of the file system
    read(fd,f,1024);
    //This is a array to store the name read from inode
    char namex[8];
    //This is index of the first character of the name of that inode
    int current_location = 128+(i*48);
    //Read the name from inode
    for (int j = 0; j < 8; ++j)
    {
      namex[j] = f[current_location+j];
    }

    if(strcmp(namex,name)==0){
      //if the name is same, we get the block that is the in position of blockNum
      int x = f[current_location+11+4*(blockNum+1)];
      //Then we go to the specific block that we need to write
      lseek(fd,1024*(x),SEEK_SET);
      //Then write the data into that block.
      write(fd,buf,1024);
    }
  }
  //close file
  close(fd);
}
