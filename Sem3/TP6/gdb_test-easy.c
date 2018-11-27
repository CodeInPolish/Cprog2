#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
  int i,j;
  char** tab;

  if (!(tab = (char**) malloc((10)*sizeof(char*)))) {
    perror("Erreur d'allocation de memoire: tab\n");
    exit(1);
  }

  for (i=0; i<8; i++) {    
    if (!(tab[i] = (char*) malloc(15*sizeof(char)))) {
      perror("Erreur d'allocation de memoire: tab[i]\n");
      for (j=0; j<i; j++) free(tab[j]);
      free(tab);
      exit(1);
    }
  }
	
  for (i=0; i<10; i++) { 
	for (int k = 0; k<15; k++){
		tab[i][k] = 42;
	} 
  }

  for (i=0; i<10; i++)
    free(tab[i]);
  free(tab);
  
  exit(0);
}
