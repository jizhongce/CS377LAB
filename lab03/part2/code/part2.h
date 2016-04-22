#ifndef __FILE_SYSTEM_INTERFACE_H
#define __FILE_SYSTEM_INTERFACE_H

/*This is the interface of the part2, we will implement in the part2.c*/

/*
The create function will take two arguements one is the file name which will have maximum 8 characters
The second arguement is size which means how many block the file will use.The the create function will
create file in the file system, First, we will read first 1024 bytes which is super block, Then we will
use a loop to check free list which indicate which block is free. So if the block is free, then we change
it to 1 which means this block will be used and we get the block number and store it into an array so we
can use it later. We will continue to check if the number of block is less than the size. After check and
set the freelist, we have to find a free inode, So we will check each inode to see if it is used or not.
Here we will use a helper method which called inode_used, this method will return the index of the used of
that inode so that we can check whether the inode is used or not. After we find a free inode, we will write
the name and size into this inode. And also will write the block that the file will used in file system into
the block pointer. After taht we will wirte the buffer back to the file system.
*/
void f_create(char name[8],  int size);

/*
The delete function will take only one arguement which is file name, Then we will delete the file whose name
is input file name. The idea is that first we will check each inode's name to find the specific inode whose
name is file name. Then we will get the block number that the file used. Then we delete the file name, size
and also the block pointer. Then we set this inode as free. Then we have to go back to check the free list,
and set block that the file used as free so that next create file can use these block. We do not delete the
file in the block because it will be automaticly overwirten when other file is going to write data into that
block
*/
void f_delete(char name[8]);

/*
The read function will take three arguements which are file name, block number and a buffer. The function
will read the file whose name is input file name in specific block and read the data in that block into the
buffer. The idea to inplement this fuction is that first we will read the super block and check each inode to
find the inode whose name is the input file name, then we can get the block pointer of that inode. Then we can
get which block in the file system we want to read. Then we read the data from that specific block and put the
data in the buffer.
*/
void f_read(char name[8], int blockNum, char buf[1024]);

/*
The write function is quite similar to the read function, the wirte function also take three arguements which are
name, blockNum and a buffer. name indicates which file we need to write, blockNum indicates the specific block number
we need to write to. The buf is a buffer which contains the data we need to write into that block. First we read the
super block from the file system. Then we check each inode to find which inode has same name as the input file name
then we get the block_pointer and find which block is we need. Then we write the data into that block.
*/
void f_write(char name[8], int blockNum, char buf[1024]);

/*
The ls function will list all the files in the file system and their size.
The idea to implement this function is that we can check each inode, so if inode is used which means
this inode contain file's information, so we can get the name and size of the file then print out the
name and size. So first we will read the first block which is super block from the file system. In the
super block, we can find the freelist and inode. The first 128 bytes means the freelist of the file
system which indicates which block is free. Then rest of them is inode. Then we set the location is 128
which is the beginning of the inode and it also is the first chatacter of the first file's name. Then
we use a helper method inode_used to check the inode is used or not. if the inode is used, we read the
name from file system into the name array. Then we get the size of that file. Finally we print out the
output. We will check each inode to get all existed file's name. After that we will write the buffer back
into the file system.
*/
void ls();

#endif
