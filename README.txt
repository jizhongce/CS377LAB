shengbo lou: 28530995
zhongce ji: 28551884
yucheng lu: 28411887


Makefile: for compiling all files

part1:
  1.use fork(),sleep() and waitpid().
  2.check if fork() == 0 to determine whether it's child or not.
  3.sleep 10 sec for Grandchild
  4.print out ID for child, Grandchild and parent.


part2:
  1.get the user input process ID.
  2.call kill() command to kill the process.
  3.switch errno to handle all the errors.
  4.print out error messages.

part3:
  1.create the shell and using infinite while loop to keep it running
  2.get user input string using fgets().
  3.split the string by " "(space) to get an array of commands.
  4.using for loop to get every command
  5.using fork() here to create children and execute command
  6.if execl() returns error, handle the error and print out error message.
