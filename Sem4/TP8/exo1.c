#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t nbElem(char**);

void main(){
	char* tabptr[10] = {"Exercices","de","langage","C","2eme","bloc"};

	size_t nbElement = nbElem(tabptr);
	char** dyntab = (char**) malloc(nbElement*sizeof(char*));
	for(int i=0;i<nbElement;i++){
		size_t strLen = strlen( *(tabptr+i));
		*(dyntab+i)= malloc((strLen+1)*sizeof(char));
		strcpy( *(dyntab+i), *(tabptr+i)); 
	}

	for(int i=0;i<nbElement;i++){
		for(int j=0;j<10;j++){
			printf("%c",dyntab[i][j]);
		}
	}

	exit(0);
}

size_t nbElem(char** ptr){
	size_t ret=0;
	while( *(++ptr) ){
		ret++;
	}
	return ret+1;
}