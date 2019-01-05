#include <stdbool.h>
#include <stdio.h>

#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#define MAX_ID_TEMP 30
#define MAX_MESSAGE 50
#define DEFAULT_SIZE 10

typedef struct{
	int id;
	double temp;
	char* message;
} Temperature;

typedef struct{
	Temperature* tab;
	int tailleLog;
	int taillePhys;
} TempArray;

TempArray readTemperatures();
bool writeTemperature(FILE* f, Temperature temp);
bool readTemperature(FILE* f, Temperature* temp);
bool writeFile(char* path, TempArray t);
bool readFile(char* path, TempArray* t);
void print(TempArray t);
int nbrPos(TempArray t);
void filter(TempArray t1, TempArray* t2);
void sortTemperatures(TempArray* t);
int cmptemp(const void* t1,const void* t2);
void freeMem(TempArray* t);
#endif