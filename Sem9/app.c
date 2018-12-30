#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

int main(int argc, char** argv){
	Livre l;
	while(1){
		_Bool val = lireLivre(&l);
		printf("Added: %s\n", (val != 0 ? "true" : "false"));
		printf("Livre: %s\n", livre2str(l));
	}
	exit(0);
}