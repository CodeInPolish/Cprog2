#include <stdio.h>
#include <stdlib.h>

int tab[50][50];

void populateTab(int m, int n){
	int iLin, iCol;
	char element='A';

	while(iLin<m){
		while(iCol<n){
			tab[iLin][iCol]=element;
			element++;
			if(element>'Z'){
				element='A';
			}
			iCol++;
		}
		iCol=0;
		iLin++;
	}
}

void checkTab(int m, int n){
	int iLin=0, iCol=0;
	char element='A';

	while(iCol<n){
		while(iLin<m){
			if(element == tab[iLin][iCol]){
				printf("%c: ligne %d, colonne %d\n",element, iLin, iCol);
			}
			element++;
			if(element>'Z'){
				element='A';
			}
			iLin++;
		}
		iLin=0;
		iCol++;
	}
}

void freq(int m, int n){

	printf("\n");
	printf("        ");
	for(int i=0;i<26;i++){
		printf(" %c ",(char)i+'A');
	}
	printf("\n");

	int iLin=0;

	while(iLin<m){
		printf("Ligne %d:", iLin);
		for(int i=0;i<26;i++){
			int count=0;

			for(int iCol=0;iCol<n;iCol++){
				if(tab[iLin][iCol] == (char)i+'A'){
					count++;
				}
			}

			printf(" %d ", count);
		}
		printf("\n");
		iLin++;
	}

}


void main(){
	int m,n;

	int car;
	printf("Entrez m: ");

	while((car = getchar())!=EOF){
		if(getchar() == '\n' && car > 47 && car < 58){
			m = car-'0';
			break;
		}		
	}

	printf("Entrez n: ");
	
	while((car = getchar())!=EOF){
		if(getchar() == '\n' && car > 47 && car < 58){
			n = car-'0';
			break;
		}
	}

	populateTab(m,n);

	checkTab(m,n);

	freq(m,n);

	exit(0);
}