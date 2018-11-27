#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
    int nLignes, nCol;
    char **cases;
    int *remplissageCol;
    char pionJoueur = 'X';
    char pionJouePas = 'O';

    printf("H = ?\n");
    scanf("%d", &nLignes);
    printf("L = ?\n");
    scanf("%d", &nCol);
    printf("\n");

    // Allocation de la matrice et du tableau de positions des jetons
    cases = (char **)malloc(nCol*sizeof(char *));
    remplissageCol = (int *)malloc(nCol*sizeof(int));
    if (cases == NULL || remplissageCol == NULL){
        perror("Probleme memoire!\n");
        exit(1);
    }
    for (int j = 0; j < nCol; j++){
        cases[j] = (char *)malloc(nLignes*sizeof(char));
        if (cases[j] == NULL){
            perror("Probleme memoire!\n");
            exit(1);
        }
    }

    // Initialisation de la matrice
    for (int j = 0; j< nCol; j++){
        remplissageCol[j] = nLignes-1;
        for (int i = 0; i < nLignes; i++){
            cases[j][i] = '.';
        }
    }

    // Jeu
    int colJoueur;
    do{
        // Permutation des joueurs
        char temp = pionJoueur;
        pionJoueur = pionJouePas;
        pionJouePas = temp;

        // Affichage tableau
        for (int i = 0; i < nLignes; i++){
            for (int j = 0; j< nCol; j++){
                printf("%2c", cases[j][i]);
            }
            printf("\n");
        }

        // Lecture de la colonne où jouer
        printf("Colonne joueur %c ? ", pionJoueur);
        scanf("%d", &colJoueur);

        // Cas de la colonne pleine
        if (colJoueur>0 && colJoueur<=nCol && remplissageCol[colJoueur-1] < 0){
            printf("Colonne pleine!\n");
            continue;
        }

        // Cas de placement d'un pion
        if (colJoueur>0 && colJoueur<=nCol){
            cases[colJoueur-1][remplissageCol[colJoueur-1]] = pionJoueur;
            remplissageCol[colJoueur-1]--;
        }

        // Cas du rajout de colonne
        else if (colJoueur>nCol){
            nCol++;
            cases = (char **)realloc(cases, nCol*sizeof(char *));   // check allocation error
            cases[nCol-1] = (char *)malloc(nLignes*sizeof(char));   // check allocation error
			remplissageCol = (int *)realloc(remplissageCol, nCol*sizeof(int));  // check allocation error
            remplissageCol[nCol-1] = nLignes-1;
            for (int i=0; i<nLignes; i++){
                cases[nCol-1][i] = '.';
            }
        }

        // Cas de la suppression d'une colonne
        else if (colJoueur<0 && -colJoueur<=nCol){
            int colADetruire = -colJoueur-1;
            free(cases[colADetruire]);
            // On decale toutes les colonnes vers la gauche
            for (int j = colADetruire; j<nCol; j++){
                cases[j] = cases[j+1];
                remplissageCol[j] = remplissageCol[j+1];
            }
            nCol--;
            // Ici taille logique == taille physique
			if (nCol == 0) {
				free(cases);
				free(remplissageCol);
			} else {
				cases = (char **)realloc(cases, nCol*sizeof(char *));   // check allocation error
				remplissageCol = (int *)realloc(remplissageCol, nCol*sizeof(int));  // check allocation error
			}
        }
    } while (nCol != 0);

    printf("Fin de partie!\n");
    exit(0);
}
