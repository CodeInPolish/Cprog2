#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temperature.h"

int main(int argc, char** argv){
	TempArray tab = readTemperatures();

	printf("LogSize: %d\n", tab.tailleLog);
	printf("PhysSize: %d\n", tab.taillePhys);

	print(tab);

	TempArray* read = (TempArray*) malloc(sizeof(TempArray));
	readFile("test2",read);
	print(*read);

	//freeMem(read);
	freeMem(&tab);
	exit(0);
}