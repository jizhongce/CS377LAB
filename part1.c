#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int i;
	i = fork();
	if(i==0){
		int k;
		k = fork();
		if(k==0){
			sleep(10);
			printf("Grandchild process with process id %d has completed.\n", getpid());
		}
		else{
			waitpid(-1,NULL,0);
			printf("Child process with process ID %d has completed.\n", getpid());
		}
	}
	else{
      	waitpid(-1,NULL,0);
		printf("Parent process with process ID %d has finished.\n", getpid());
	}
	return 0;
}