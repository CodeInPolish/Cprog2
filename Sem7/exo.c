#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bool.h>

#define DEFAULT_SIZE 3
#define BUFFER_SIZE 10

void imprimerTable(char* , int*, int);
char* lireLigne();
bool ajouterTable(int**, int*, int*, int);
int chargerTable(char**, int, int **, int*);


void main(int argc, char** argv){
    int logSize = 0;
    int physSize = 0;
    int** tab=NULL;

    imprimerTable("table avant traitement:", tab, logSize);

    if(argc>1){
        logSize = chargerTable(argv+1, argc-1, tab, &physSize);
        if(logSize < 0){
            printf("erreur chargement table");
            exit(1);
        }
        imprimerTable("table chargee", tab, logSize);
    }



    exit(0);
}

void imprimerTable(char* leg, int* tab, int sz){
    printf("%s\n", leg);
    for(int i=0; i<sz;i++){
        printf("%d\n", *(tab+i));
    }
}

char* lireLigne(){
    int buffer[BUFFER_SIZE];
    int* str=NULL;
    while(fgets(buffer, BUFFER_SIZE, stdin)){
        int len = strlen(buffer);

        if(buffer[len-1]=='\n'){
            len--;
        }

        if(str==NULL){
            str = (char*) malloc((len+1)*sizeof(char));
            if(str==NULL){
                return NULL;
            }
            strncpy(str,buffer,len);
        }else{
            str = (char*) realloc(str, (strlen(str)+len+1)*sizeof(char));
            if(str==NULL){
                return NULL;
            }
            strncat(str,buffer,len);
        }
       
       if(buffer[strlen(buffer)-1] == '\n'){
           return str;
       }
    }

    return NULL;
}

bool ajouterTable(int** tab, int* tailleL, int* tailleP, int x){
    if(tab==NULL){
        *tailleL = 0;
        *tailleP = DEFAULT_SIZE;
        *tab = (int*) malloc(*tailleP*sizeof(int);

        if(*tab==NULL){
            return false;
        }
    }

    if(*tailleL==*tailleP){
        *tailleP *=2;
        *tab = (int*) realloc(*tab, *tailleP*sizeof(int));
        if(*tab==NULL){
            return false;
        }
    }

    *(tab+*tailleL) = x;
    (*tailleL)++;
    return true;
}

int chargerTable(char** mots, int nbrMots, int** tab, int* tailleP){
    int logSize = 0;
    for(int i=0;i<nbrMots;i++){
        if(!ajouterTable(tab, &logSize, tailleP, atoi(mots[i])){
            return -1;
        }
    }
    return logSize;
}