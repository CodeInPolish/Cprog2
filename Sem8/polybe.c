#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "crypt.h"

#define NUMBER_OF_CHARS 64

const char characters[] = { 'A','B','C','D','E','F','G','H',
							'I','J','K','L','M','N','O','P',
							'Q','R','S','T','U','V','W','X',
							'Y','Z','0','1','2','3','4','5',
							'6','7','8','9',' ','!','"','#',
							'$','%','&','\'','(',')','*','+',
							',','-','.','/',':',';','<','=',
							'>','?','@','[','\\',']','^','_'};

const int values[] = { 11,21,31,41,51,61,71,81,
						12,22,32,42,52,62,72,82,
						13,23,33,43,53,63,73,83,
						14,24,34,44,54,64,74,84,
						15,25,35,45,55,65,75,85,
						16,26,36,46,56,66,76,86,
						17,27,37,47,57,67,77,87,
						18,28,38,48,58,68,78,88};


char* encrypt(char* str){
	int len = strlen(str);
	if(str[len-1] == '\n'){
		len--;
	}
	char* crypted = (char*) calloc((2*len+1),sizeof(char));
	for(int i=0;i<len;i++){
		int index;
		for(int j=0;i<NUMBER_OF_CHARS;j++){
			if(characters[j] == str[i]){
				index = j;
				break;
			}
		}
		char buffer[2];
		sprintf(buffer, "%d", values[index]);
		strncat(crypted, buffer, 2);
	}
	return crypted;
}

char* decrypt(char* str){
	int len = strlen(str);
	if(str[len-1] == '\n'){
		len--;
	}
	char* decrypted = (char*) calloc((len/2)+1, sizeof(char));
	for(int i=0;i<len;i+=2){
		int value = (int) ((str[i]-'0')*10 + (str[i+1]-'0'));
		int index;
		if(value > 10 && value < 89){
			for(int j=0;j<NUMBER_OF_CHARS;j++){
				if(value == values[j]){
					index=j;
				}
			}
			char buffer[1];
			buffer[0] = characters[index];
			strncat(decrypted,buffer,1);
		}
		
	}
	return decrypted;
}