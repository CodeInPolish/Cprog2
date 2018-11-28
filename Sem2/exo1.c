#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

int tab[SIZE];

int moy(int elemNo){
	int total=0, i=0;

	while(i<elemNo){
		total +=tab[i];
		i++;
	}

	return (total/elemNo);

}

int var(int moy, int elemNo){
	int result=0, i=0;

	while(i<elemNo){
		result = result + (tab[i]-moy);
		i++;
	}

	return result;
}

int varSquared(int var){
	return var*var;
}

void main (){

	int elemNo=0;
	int score;
	while(scanf("%d", &score)){
		tab[elemNo] = score;
		elemNo++;
	}

	int moyenne = moy(elemNo);
	int std_dev = var(moyenne, elemNo);
	int sq_dev = varSquared(std_dev);

	printf("Moyenne: %d, Std-Dev: %d, var: %d\n",moyenne, std_dev, sq_dev);

	exit(0);
}