#include <stdlib.h>
#include <stdio.h> 

int fact(int number){
	int counter=1;
	int result=1;

	if(number < 2){
		return 1;
	}

	if(number>11){
		return 0;
	}

	while(counter<number+1){
		result = result*counter;
		counter++;
	}

	return result;
}

void main() {

	printf("%d\n", fact(0));
	printf("%d\n", fact(1));
	printf("%d\n", fact(2));
	printf("%d\n", fact(3));
	printf("%d\n", fact(4));
	printf("%d\n", fact(5));
	printf("%d\n", fact(6));
	printf("%d\n", fact(7));
	printf("%d\n", fact(8));
	printf("%d\n", fact(9));
	printf("%d\n", fact(10));
	printf("%d\n", fact(11));
	printf("%d\n", fact(12));
	printf("%d\n", fact(13));

	exit(0);
}