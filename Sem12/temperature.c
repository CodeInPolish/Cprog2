#include <string.h>
#include <stdlib.h>
#include "temperature.h"

		

TempArray readTemperatures(){
	TempArray array;
	array.tab = (Temperature*) calloc(DEFAULT_SIZE, sizeof(Temperature));
	array.tailleLog = 0;
	array.taillePhys = DEFAULT_SIZE;

	char buffer[MAX_MESSAGE+MAX_ID_TEMP];
	char* message;
	int i=0, id;
	double temp;
	while(fgets(buffer, MAX_MESSAGE+MAX_ID_TEMP, stdin)!=NULL){
		if(i==0){
			id = (int) strtol(strtok(buffer, " "), NULL, 10);
			temp = strtod(strtok(NULL," "), NULL);
		}
		else{
			int len = strlen(buffer);
			if(buffer[len-1] == '\n'){
				buffer[len] = '\0';
				len--;
			}

			message = (char*) calloc(len+1, sizeof(char));
			strncpy(message, buffer, len);
		}

		i++;
		if(i>1){
			Temperature current = {id, temp, message};
			array.tab[array.tailleLog] = current;
			array.tailleLog++;
			i=0;
		}

		if(array.tailleLog == array.taillePhys){
			array.taillePhys*=2;
			array.tab = (Temperature*) realloc(array.tab, array.taillePhys*sizeof(Temperature));
		}
	}

	return array;
}

bool writeTemperature(FILE* f, Temperature temp){
	int size = (int) strlen(temp.message);
	int written = 3;
	written -= fwrite(&(temp.id), sizeof(int), 1, f);
	written -= fwrite(&(temp.temp), sizeof(double), 1, f);
	written -= fwrite(&size, sizeof(int), 1, f);
	if(size > 0){
		written ++;
		written -= fwrite(temp.message, size*sizeof(char), 1, f);
	}
	
	if(written == 0){
		return true;
	}
	else{
		return false;
	}
}

bool readTemperature(FILE* f, Temperature* temp){
	int read = 3;
	read -= fread(&(temp->id), sizeof(int), 1, f);
	read -= fread(&(temp->temp), sizeof(double), 1, f);
	int size=0;
	read -= fread(&size, sizeof(int), 1, f);
	temp->message = (char*) calloc((size+1), sizeof(char));
	if(size>0){
		read ++;
		read -= fread(temp->message, size*sizeof(char), 1, f);
	}

	if(read == 0){
		return true;
	}
	else{
		return false;
	}
}

bool writeFile(char* path, TempArray t){
	FILE* f = fopen(path, "ab");

	if(f==NULL){
		return false;
	}

	for(int i=0;i<t.tailleLog;i++){
		if(!writeTemperature(f,t.tab[i])){
			return false;
		}
	}

	fclose(f);
	return true;
}

bool readFile(char* path, TempArray* t){
	FILE* f = fopen(path, "rb");

	if(f == NULL){
		return false;
	}

	t->tab = (Temperature*) malloc(DEFAULT_SIZE*sizeof(Temperature));
	t->tailleLog = 0;
	t->taillePhys = DEFAULT_SIZE;
	Temperature buffer;
	int index = 0;
	while(readTemperature(f, &buffer)) {
		t->tab[t->tailleLog] = buffer;
		if(t->tailleLog==t->taillePhys){
			t->taillePhys*=2;
			t->tab = realloc(t->tab, t->taillePhys*sizeof(Temperature));
		}
		t->tailleLog++;
	}

	fclose(f);
	return t->tailleLog != 0 ? true : false;
}

void print(TempArray t){
	for(int i=0;i<t.tailleLog;i++){
		printf("%d: %f°C", t.tab[i].id, t.tab[i].temp);
		if(strlen(t.tab[i].message)>1){
			printf(" (%s)\n", t.tab[i].message);
		}
		else{
			printf("\n");
		}
	}
}

int nbrPos(TempArray t){
	int count=0;
	for(int i=0;i<t.tailleLog;i++){
		if(t.tab[i].temp >= 0){
			count++;
		}
	}
	return count;
}

void filter(TempArray t1, TempArray* t2){
	int index=0;
	for(int i=0;i<t1.tailleLog;i++){
		if(t1.tab[i].temp>=0){
			t2->tab[index] = t1.tab[i];
			index++;
		}
	}
}

void freeMem(TempArray* t){
	for(int i=0;i<t->tailleLog;i++){
		free(t->tab[i].message);
	}
	free(t->tab);
}