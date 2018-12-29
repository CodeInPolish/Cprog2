#include <stdlib.h>
#include <string.h>
#include "crypt.h"

char* rot13(char*);

char* encrypt(char* str){
	return (char*) rot13(str);
}

char* decrypt(char* str){
	return (char*) rot13(str);
}

char* rot13(char* str){
	int len = strlen(str);
	char* rotated = (char*) calloc(len+1, sizeof(char));
	for(int i=0;i<len;i++){
		if(str[i] > '@' && str[i] < '['){
			//majuscule
			rotated[i] = (str[i]+13 >= '[') ? str[i]+13-26 : str[i]+13;			
		}
		else if(str[i] > '`' && str[i] < '{'){
			//miniscule
			rotated[i] = (str[i]+13 >= '{') ? str[i]+13-26 : str[i]+13;
		}
		else{
			rotated[i] = str[i];
		}
	}

	return rotated;
}