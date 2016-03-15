# Lab 1

## Team Members:
shengbo lou: 28530995<br>
zhongce ji: 28551884<br>
yucheng lu: 28411887


## Makefile: for compiling all files

#### part1:
  * use fork(),sleep() and waitpid().
  * check if fork() == 0 to determine whether it's child or not.
  * sleep 10 sec for Grandchild
  * print out ID for child, Grandchild and parent.


#### part2:
  * get the user input process ID.
  * call kill() command to kill the process.
  * switch errno to handle all the errors.
  * print out error messages.

#### part3:
  * create the shell and using infinite while loop to keep it running
  * get user input string using fgets().
  * split the string by " "(space) to get an array of commands.
  * using for loop to get every command
  * using fork() here to create children and execute command
  * if execl() returns error, handle the error and print out error message.
