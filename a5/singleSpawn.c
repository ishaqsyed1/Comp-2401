#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
//Declaring the function before utilizing
int morph(char *number);

int main(int argc, char* argv[]) {
	int state;
	int final;
	if(argv[1] == NULL){
		printf("Please enter a positive number with the call\n");
	}
	else{
    		
		pid_t p = fork();
		if (p != 0){
			while(wait(&state) != p){
				//PERFORM NOTHING
			}
			final = WEXITSTATUS(state);
			if(final == 1){
			printf("The number %s is a prime number.\n", argv[1]);
			}
			else if(final == 0){
			printf("The number %s is not a prime number.\n", argv[1]);
			}
		}
    		else{
      			morph(argv[1]);
    		}
	}
}

int morph(char *number){
  	char * fileName = "./isPrime";
	char * paramList[3] = {"isPrime",number};
	int result = execvp(fileName,paramList);
  	if (!result){
   		return -1;
  	}
  	else{
    		return result;
  	}
}
