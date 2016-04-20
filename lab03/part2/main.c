#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "part2.h"

//create a duumy buff for the file
void createDummyBuff(char name[8],int size, char buf[1024]){
  char tmp[16] = {'T','h','e',' ',size+48,' ','b','l','o','c','k',' ','f','o','r',' '};
  for (int i=0; i<16;i++) {
    buf[i] = tmp[i] ;
  }
  for (int i=0; i<8;i++) {
    buf[16+i] = name[i] ;
  }
  for (int i=0; i<1000;i++) {
    buf[24+i] = 'a' + (rand() % 26);;
  }
}

int main(){
  //open the input file
  FILE *fp = fopen("data/input.txt","r");

  //create a dummy buf for writing
  char buf[1024];
  for (int i=0; i<1024;i++) {
    /* code */
    buf[i] = 'b';
  }
  //get the disk name from the first line of the input file
  char disk_name;
  fscanf(fp,"%s",&disk_name);


  //create disk by using the given file
  char command[90];
  strcpy(command, "./create ");
  strcat(command,&disk_name);
  system(command);

  //This is use to store the type of the action
  char type[1];
  //read the file until the last
  while (fscanf(fp,"%s",type)!=-1) {
      // printf("%s\n", type);s
    //create file
    //If the type of action is C, then we get the name and size of the file and call the create file function
    if(strcmp(type,"C")==0){
      char name[8];
      int size;
      //read the name of the file
      fscanf(fp,"%s",name);
      //read the size of the file
      fscanf(fp,"%i",&size);
      //call the function to create a file
      f_create(name,size);
    }
    //list file
    //If the type of action is L, then we list all the file in the file system
    else if(strcmp(type,"L")==0){
      //here we call the ls function to list file
      ls();
    }
    //write
    //If the type of action is C, then we get the name and size of the file and call the create file function
    else if(strcmp(type,"W")==0){
      char name[8];
      int size;
      //read the name of the file
      fscanf(fp,"%s",name);
      //read the block number of the file
      fscanf(fp,"%i",&size);
      //Here we call the create function to write the specific block of that file
      createDummyBuff(name,size,buf);
      f_write(name,size,buf);
    }
    //delete file
    else if(strcmp(type,"D")==0){
      char name[8];
      //read the name of the file
      fscanf(fp,"%s",name);
      //Here we call the delete function to delete the file
      f_delete(name);
    }
    //read file
    else{
      char name[8];
      int size;
      //read the name of the file
      fscanf(fp,"%s",name);
      //read the block number of the file
      fscanf(fp,"%i",&size);
      //create a buffer to store the data read form the block
      char buf2[1024];
      //Here we call the create function to read the specific block of that file
      f_read(name,size,buf2);
    }

  }
  //close file
  fclose(fp);

}
