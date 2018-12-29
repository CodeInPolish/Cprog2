#include <stdlib.h>
#include <stdio.h>
#include "crypt.h"

int main(int argc, char** argv){
	if(argc>1){
		printf("Programme en cours: %s\n", ((*argv)+=2));
		for(char** ptr=argv+1;ptr<argv+argc;ptr++){
			char* encrypted = encrypt(*ptr);
			printf("%s ", encrypted);
			free(encrypted);
		}
		printf("\n");
	}
	else{
		printf("Error: no arguments passed.\n");
	}
	exit(0);
}