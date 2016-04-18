#ifndef __FILE_SYSTEM_INTERFACE_H
#define __FILE_SYSTEM_INTERFACE_H

int f_create(char name[8], int size);

int f_delete(char name[8]);

int f_read(char name[8], int blockNum, char buf[1024]);

int f_write(char name[8], int blockNum, char buf[1024]);

void ls();

#endif
