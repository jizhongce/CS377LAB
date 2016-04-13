#ifndef __FILE_SYSTEM_INTERFACE_H
#define __FILE_SYSTEM_INTERFACE_H

int create(char name[8], int size);

int delete(char name[8]);

int read(char name[8], int blockNum, char buf[1024]);

int write(char name[8], int blockNum, char buf[1024]);

void ls();

#endif
