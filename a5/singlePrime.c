#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

int main(int argc, char* argv[]) {

	if(argc != 2){
		printf("Usage: singlePrime filename\n");
	}
	else{
    		FILE *file;
		unsigned int a;
		char buffer[100];
   		file = fopen(argv[1], "r");
    		if (file){
			fseek(file, 0, SEEK_SET);
			int read = fread(&a,4,1,file);
			if(read != 1){
				//nothing to do
			}
			else{
				sprintf(buffer, "%d \n", a);
				morph(buffer);
			}
		}
    		
    		else{
      			printf("file %s does not exist\n", argv[1]);
    		}
  	};
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
