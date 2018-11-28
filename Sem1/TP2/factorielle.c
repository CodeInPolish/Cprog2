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

	while(1){
		int read = getchar();

		if(read > 47 & read < 58){
			int read2 = getchar();
			if(read2 == 10){
				printf("%d! = %d\n", read-48, fact(read-48));
			}
			else if(read2 > 47 & read < 58 && getchar() == 10){
				int number=(read-48)*10 + read2-48;
				if(number < 13){
					printf("%d! = %d\n", number, fact(number) );
				}
				else{
					printf("Error: integer overflow\n");
				}
				
			}
			else{
				printf("Error: too many characters\n");
				while(getchar()!=10);
			}
		}
		else if(read < 0){
			break;
		}
		else if(read == 10){
			printf("Error: Empty line\n");
		}
		else{
			printf("Error: enter a number between 0 and 9\n");
			while(getchar()!=10);
		}
	}

	exit(0);
}