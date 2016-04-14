#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
// #include "part2.h"


void ls(){

}

void create(char name[8], int size){
    int fd;
    char *buf;

    buf = (char *) calloc(1024,sizeof(char));

    fd = open("file2",O_RDWR);

    if(read(fd,buf,1024)<0){
      printf("empty\n");
    }
    lseek(fd,0,SEEK_SET);

    buf[2] = 'a';

    if(write(fd,buf, 1024)<0)
    printf("error: write failed \n");

    //printf("%c\n", buf[0]);

    close(fd);

}

// int delete(char name[8]){
//   return 1;
// }

// int read(char name[8], int blockNum, char buf[1024]){
//   return 1;
// }

// int write(char name[8], int blockNum, char buf[1024]){
//   return 1;
// }
