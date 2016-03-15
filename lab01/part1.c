#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int i;
	//fork process
	i = fork();

	//if it's children
	if(i==0){
		int k;
		//create Grandchild
		k = fork();
		if(k==0){
			//if it's Grandchild, sleep 10 sec
			sleep(10);
			//output of Grandchild
			printf("Grandchild process with process ID %d has completed.\n", getpid());
		}
		else{
			//wait Grandchild process finish
			waitpid(-1,NULL,0);
			//output of child
			printf("Child process with process ID %d has completed.\n", getpid());
		}
	}
	else{
		 		//parent wait all children
      	waitpid(-1,NULL,0);
				//output of parent
				printf("Parent process with process ID %d has finished.\n", getpid());
	}
	return 0;
}
