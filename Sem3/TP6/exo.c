#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** allocateArray(int,int);
void freeArray(char**,int);
bool placeInArray(char**,int,int,int,char);
void destroyCol(char**,int,int);
char** addCol(char**,int,int,int);
void printArray(char**,int,int);


char** allocateArray(int h, int l){
	char **arr;

	arr = (char**) malloc(l*sizeof(char*)); 

	for(int i=0;i<l;i++){
		arr[i] = (char*) malloc(h*sizeof(char));
	}

	return arr;
}

void freeArray(char** arr, int l){
	for(int i=0; i<l; i++){
		free(arr[i]);
	}

	free(arr);
}

bool placeInArray(char** arr,int h, int l, int col, char player){
	if(col>-1 && col<l){
		int i=h-1;

		while(i >= 0){
			if(arr[col][i] == 'X' || arr[col][i] == 'O'){
				i--;
			}
			else{
				arr[col][i] = player;
				return true;
			}			

		}

		return false;
	}
	return false;
}

void destroyCol(char** arr,int l, int col){
	free(arr[col]);

	for(int i=col;i<l-1;i++){
		arr[i]=arr[i+1];
	}
}

char** addCol(char** arr, int currL, int maxL, int h){
	char** newArr;
	if(currL>=maxL){
		newArr = (char**) realloc(arr,(maxL+1)*sizeof(char*));
		newArr[maxL] = (char*) malloc(h*sizeof(char));	
	}
	else{
		arr[currL] = (char*) malloc(h*sizeof(char));
	}

	return newArr != NULL ? newArr : arr;
}

void printArray(char** arr, int h, int l){
	for(int iCol=0;iCol<h;iCol++){
		for(int iLin=0;iLin<l;iLin++){
			char elem = arr[iLin][iCol];

			if(elem != 'X' && elem != 'O'){
				printf(" . ");
			}
			else{
				printf(" %c ", elem);
			}
		}
		printf("\n");
	}
}

void main(){

	int h=0,maxL=0;
	int currL=0;
	bool order=true;

	printf("H = ?\n");
	scanf("%d",&h);
	printf("L = ?\n");
	scanf("%d",&maxL);

	currL = maxL;

	char** myArray = allocateArray(h,maxL);

	while(true){
		printArray(myArray,h,currL);

		if(order){
			printf("X turn: \n");
			int col=0;
			scanf("%d",&col);
			if(col<0){
				destroyCol(myArray, currL, (col+1)*(-1));
				currL--;
			}
			else if(col>currL){
				myArray = addCol(myArray, currL, maxL, h);
				if(currL==maxL){
					maxL++;
				}
				currL++;
			}
			else{
				placeInArray(myArray,h,currL,col-1,'X');
			}
			order=!order;
		}else{
			printf("O turn: \n");
			int col=0;
			scanf("%d",&col);
			if(col<0){
				destroyCol(myArray,currL,(col+1)*(-1));
				currL--;
			}
			else if(col>currL){
				myArray = addCol(myArray, currL, maxL, h);
				if(currL==maxL){
					maxL++;
				}
				currL++;
			}
			else{
				placeInArray(myArray,h,currL,col-1,'O');
			}
			order=!order;
		}

	}

	freeArray(myArray,currL);

	exit(0);
}