#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
//Declaring the function before utilizing
int morph(char *number);

int main(int argc, char *argv[]) {
	FILE *file = NULL;
	FILE *file2 = NULL;
  	int test;
  	int integer[10];

	if (argc < 2) {
    		printf("usage %s filename \n", argv[0]);
    		return(1);
  	}

  	test = 0;
  	file = fopen(argv[1], "rb+");
  	if (file == NULL){
		test = 0;
	}

	else{
		test = 1;
	}
  	fclose(file);

	if (test != 0) {
		int size;
    		char intstring[10][100];

   		file2 = fopen(argv[1], "rb+");
    		fseek(file2, 0, SEEK_END);
    		size = (ftell(file2)/sizeof(int));
    		fseek(file2, 0, SEEK_SET);

    		if (size > 10){
			size = 10;
		}

		int i;
    		for (i=0; i<size; i++) {
      			fread(&integer[i], sizeof(int), 10, file2);
      			sprintf(intstring[i], "%d", integer[i]);
    		}

    		int clist[size];
		char plist[size][100];
		int p, j, listsize, k, l, m;

    		for (j=0; j<size; j++) {
     			p = fork();
      			if (p != 0){
				clist[j] = p;
			}
      			else{
				morph(intstring[j]);
			}
   		}
		
    		for (k; k<size; k++) {
      			int state;
      			int cp = waitpid(-1, &state, 0);
      			for(l=0; l<size; l++) {
        			if (cp >= 0) {
          				if (WIFEXITED(state)) {
            					if(cp == clist[l] && WEXITSTATUS(state) == 1) {
							strcpy(plist[listsize], intstring[l]);
              						listsize ++;

            					}
          				}
        			}
      			}
    		}
    		for (m=0; m<listsize; m++) {
      			printf("%s is a prime number \n", plist[m]);
    		}
  	}
  	else{
    		printf("File %s does not exist \n", argv[1]);
  	}

  	return 0;
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
