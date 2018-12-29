#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define InitSize 10
#define MaxLen 256

int findCoffre(char** tab, int size, char* coffre){
	for(int i=0;i<size;i++){
		if(memcmp( *(tab+i), coffre, 5)==0){
			return i;
	}
	return -1;
}

void main(int argc,char* argv[]){
	char buffer[256];
	int logSize = 0;
	int physSize = InitSize;
	char** tab = (char**) malloc(physSize*sizeof(char*));
	int size = 0;
	while(fgets(buffer, 255, stdin) != NULL){
		buffer[strlen(buffer)-1] = '\0';
		int index = findCoffre(tab, size, buffer);

		if(index>=0){
			int newSize = strlen(tab[index]) + strlen(*(buffer+5)) +1;
			tab[index] = realloc(tab[index], newSize*sizeof(char));
			strncat(*(tab+index), *(buffer+5), strlen(*(buffer+5)));
		}else{
			if(physSize==logSize){
				physSize *= 2;
				tab = (char**) realloc(tab, physSize*sizeof(char*));
			}

			tab[logSize] = (char*) malloc((strlen(buffer)+1)*sizeof(char));
			strcpy(tab[logSize], buffer);
		}
	}

	for(int i=0;i<size;i++){
		printf("%s\n", *(tab+i));
		free(*(tab+i));
	}
	free(tab);
}