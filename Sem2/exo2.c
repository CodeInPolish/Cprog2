#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int tab[100];

void deleteNonPrimes(int N){
	int i=0;

	int base=tab[i];

	while(base*base < N){
		int j=2;
		int index=i;
		while(j*base <= N){
			while(index <= N-2){
				if(tab[index] == j*base){
					tab[index] = 0;
				}
				index++;
			}
			index=0;
			j++;
		}


		i++;
		while(tab[i] == 0 && i<N-2){
			i++;
		}
		base = tab[i];
	}

}

void printPrimes(int N){
	int i=0;

	printf("1\n");

	while(i<N-2){
		if(tab[i] != 0){
			printf("%d\n", tab[i]);
		}
		i++;
	}
}

void populateTab(int N){
	int val = 2;
	int i = 0;

	while(val<=N-2){
		tab[i] = val;
		i++;
		val++;
	}
}




void main(){

	populateTab(100);
	deleteNonPrimes(100);
	printPrimes(100);
	exit(0);
}