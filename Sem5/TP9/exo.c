#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int contains(char** dict, int dict_size, char* word){
	for(int i=0;i<dict_size;i++){
		if(strcmp( *(dict+i), word) == 0){
			return 1;
		}
	}
	return 0;
}

void main(int argc, const char* argv[]){

	char** dictionnary = (char**) malloc((argc-1)*sizeof(char*));
	for(int i=0;i<argc-1;i++){
		*(dictionnary+i) = malloc(27*sizeof(char));
		strcpy( *(dictionnary+i), *(argv+i+1));
	}

	for(int i=0;i<argc-1;i++){
		printf("%d, %s\n",i, *(dictionnary+i));
	}

	unsigned long nbNotFound = 0;
	char buffer[28];
	while(fgets(buffer, 28, stdin)!=NULL){
		int len = strlen(buffer);
		buffer[len-1] = '\0';
		int presenceBit = contains(dictionnary, argc-1, buffer);
		if(presenceBit > 0){
			nbNotFound++;
			printf("%s, %ld, %s, %ld\n", buffer, strlen(buffer), "présent", nbNotFound);
		}
		else{
			printf("%s, %ld, %s, %ld\n", buffer, strlen(buffer), "absent", nbNotFound);
		}
	}

	exit(0);
}