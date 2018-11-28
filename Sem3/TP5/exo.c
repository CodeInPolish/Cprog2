#include <stdio.h>
#include <stdlib.h>

int readN(void){
	int result=0;

	while(!scanf("%d",&result));

	return result;
}

void printTable(int *t,int size){
	for(int *q=t;q-t<size;q++){
		printf(" %d ", *q);
	}
	printf("\n");
}


void main(){
	int n=0;
	int pos=0,neg=0;
	int no=0;

	n=readN();

	int number=0;

	int *posTab = malloc(n*sizeof(int));
	int *negTab = malloc(n*sizeof(int));

	while(no < n){
		if(scanf("%d",&number)){
			if(number<0){
				*(negTab+neg) = number;
				neg++;
			}else{
				*(posTab+pos) = number;
				pos++;
			}
			no++;
		}

	}

	printTable(posTab, pos);
	printTable(negTab, neg);

	free(posTab);
	free(negTab);

	exit(0);
}