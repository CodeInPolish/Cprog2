#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NB_CHAR 256   // taille maximale d'une chaîne lue sur stdin
#define NB_COFFRES 10 // taille initials du tableau de coffres
#define TAILLE_ID 5   // nombre de caractères d'un identifiant de coffres

int main (int argc, char *argv[]) {
    // Allocation de la table de coffres
    int taillePhys = NB_COFFRES;
    int tailleLog = 0;
    char** coffres = (char**) malloc(taillePhys*sizeof(char*));
    if (coffres == NULL) {
        perror("erreur d'alloc");
        exit(1);
    }
    // Remplissage du tableau avec coffres lus sur stdin
    char ligne [NB_CHAR];
    while (fgets(ligne, NB_CHAR, stdin) != NULL) {
        ligne[strlen(ligne)-1] = '\0'; // suppression de '\n'
        // Recherche du coffre dans la table
        bool contains = false;
        int i = 0;
        while (i < tailleLog && !contains) {
            if (strncmp(ligne, coffres[i], TAILLE_ID) == 0) {
                contains = true;
            } else {
                i++;
            }
        }
        // Traitement du coffre
        if (!contains) { //si la table ne contient pas le coffre
            // Cas de table pleine
            if (tailleLog == taillePhys) {
                taillePhys *= 2; // doublement de la taille physique
                if ((coffres = (char**) realloc(coffres, taillePhys * sizeof(char*))) == NULL) {
                    perror("erreur d'alloc");
                    exit(1);
                }
            }
            // Copie du nouveau coffre dans la table
            if ((coffres[tailleLog] = (char*) malloc((strlen(ligne)+1) * sizeof(char))) == NULL) {
                perror("erreur d'alloc");
                exit(1);
            }
            strcpy(coffres[tailleLog], ligne);
            tailleLog++;
        } else { // si la table contient déjà le coffre
            // Concaténation du nouveau contenu dans le coffre
            size_t tailleChaine = strlen(coffres[i]) + strlen(ligne+TAILLE_ID) + 1;
            if ((coffres[i] = (char*) realloc(coffres[i],tailleChaine*sizeof(char))) == NULL) {
                perror("erreur d'alloc");
                exit(1);
            }
            strcat(coffres[i], ligne+TAILLE_ID);
        }
    }

    // Affichage des coffres
    printf("\nCOFFRES-FORTS:\n\n");
    for (int i = 0 ; i < tailleLog; i++) {
        printf("%s\n", coffres[i]);
    }

    // Libération de la mémoire dynamique
    for (int i = 0 ; i < tailleLog; i++)
        free(coffres[i]);
    free(coffres);

    exit(0);
}
