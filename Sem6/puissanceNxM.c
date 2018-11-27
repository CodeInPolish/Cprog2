#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void afficherPlateau (char** jeu, int nc, int nl);
int lireColonne (char joueur);
bool placerPion (char** jeu, int nc, int* remplissage, char joueur, int colonne);
bool ajouterColonne (char*** jeu, int* nc, int** remplissage, int nl);
bool supprimerColonne (char*** jeu, int* nc, int** remplissage, int col);


int main() {
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
        afficherPlateau(cases, nCol, nLignes);
        // Lecture de la colonne ou jouer
        colJoueur = lireColonne(pionJoueur);
        // Cas de placement d'un pion
        if (colJoueur>0 && colJoueur<=nCol){
            if (!placerPion(cases, nCol, remplissageCol, pionJoueur, colJoueur)) {
                printf("Colonne pleine!\n");
                continue;
            }
        }
        // Cas du rajout de colonne
        else if (colJoueur>nCol){
            if (!ajouterColonne(&cases, &nCol, &remplissageCol, nLignes))
                exit(1);
        }
        // Cas de la suppression d'une colonne
        else if (colJoueur<0 && -colJoueur<=nCol){
            if (!supprimerColonne(&cases, &nCol, &remplissageCol, -colJoueur))
                exit(1);
        }
    } while (nCol != 0);

    printf("Fin de partie!\n");
    exit(0);
}



void afficherPlateau (char** jeu, int nc, int nl) {
    for (int i = 0; i < nl; i++){
        for (int j = 0; j< nc; j++){
            printf("%2c", jeu[j][i]);
        }
        printf("\n");
    }
}

bool placerPion (char** jeu, int nc, int* remplissage, char joueur, int colonne) {
    // Cas de la colonne pleine
    if (remplissage[colonne-1] < 0){
        return false;
    }
    // Cas de placement d'un pion
    jeu[colonne-1][remplissage[colonne-1]] = joueur;
    remplissage[colonne-1]--;
    return true;
}

bool ajouterColonne (char*** jeu, int* nc, int** remplissage, int nl) {
    *jeu = (char **)realloc(*jeu, (*nc+1)*sizeof(char *));
    *remplissage = (int *)realloc(*remplissage, *nc*sizeof(int));
    if (*jeu == NULL || *remplissage == NULL) {
        printf("ajouterColonne: Erreur d'allocation");
        return false;
    }
    (*jeu)[*nc] = (char *)malloc(nl*sizeof(char));
    if ((*jeu)[*nc] == NULL) {
        printf("ajouterColonne: Erreur d'allocation");
        return false;
    }
    (*remplissage)[*nc] = nl-1;
    for (int i=0; i<nl; i++){
        (*jeu)[*nc][i] = '.';
    }
    (*nc)++;
    return true;
}

bool supprimerColonne (char*** jeu, int* nc, int** remplissage, int col) {
    int colADetruire = col-1;
    free((*jeu)[colADetruire]);
    // On decale toutes les colonnes vers la gauche
    for (int j = colADetruire; j<*nc; j++){
        (*jeu)[j] = (*jeu)[j+1];
        (*remplissage)[j] = (*remplissage)[j+1];
    }
    (*nc)--;
    // Ici taille logique == taille physique
	if (*nc == 0) {
        free(*jeu);
        free(*remplissage);
	} else {
	    *jeu = (char **)realloc(*jeu, *nc * sizeof(char *));
        *remplissage = (int *)realloc(*remplissage, *nc * sizeof(int));
        if (*jeu == NULL || *remplissage == NULL) {
            printf("supprimerColonne: Erreur d'allocation");
            return false;
		}
    }
    return true;
}
