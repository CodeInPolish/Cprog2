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
	return str;
}