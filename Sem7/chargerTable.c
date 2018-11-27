#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_SIZE 3
#define BUF_LEN 10

/*
 * Vidéos associées à cette solution:
 * 
 * - Si vous vous posez des questions sur les signatures 
 *   des méthodes (combien d'étoiles etc):
 * https://youtu.be/7vpjEMquHaE
 * 
 * - Si vous voulez une explication sur les fonction chargerTable et ajouterTable:
 * https://youtu.be/cX8DPJpwbfw
 *
 * - Si vous voulez une explication sur lireLigne:
 * http://youtu.be/Zuyhvnwmlao?hd=1
 *
 * Afin d'améliorer ces vidéos, vous pouvez répondre à un petit sondage anonyme:
 * https://goo.gl/forms/sMByYEcA4UrV1v2P2
 *
 * Erratum Vidéos
 * Quelques erreurs se sont introduites dans les vidéos youtube :
 * Dans la vidéos sur les signatures de méthodes, après 3’24’’ j’introduits l’instruction *tailleL++ il faut évidemment lire (*tailleL)++
 *
 * Dans la vidéo ajouter/chargerTable :
 * Vers 4’40’’ dans le for il faut lire i et pas ptr.
 */


char* lireLigne ();
void imprimerTable (char*, int*, int);
bool ajouterTable (int**, int*, int*, int);
int chargerTable (char**, int,  int**, int*);


int main (int argc, char** argv){
    int tailleL=0, tailleP=0;
    char* ligne;
    int* tableInt = NULL;

    imprimerTable("Avant traitement: ", tableInt, tailleL);

    if ((tailleL = chargerTable(argv+1, argc-1, &tableInt, &tailleP)) == -1){
        fprintf(stderr, "Erreur: chargement table\n");
        exit(1);
    }
    imprimerTable("Table des arguments: ", tableInt, tailleL);

    printf("Entrez des entiers a ajouter a la table [Ctrl-D pour terminer]:\n");
    while ((ligne = lireLigne()) != NULL) {
        if (strlen(ligne) ==  0)
            continue;
        if (!ajouterTable(&tableInt, &tailleL, &tailleP, atoi(ligne))){
            fprintf(stderr, "Erreur: ajout table\n");
        }
    }
    imprimerTable("Table completee: ", tableInt, tailleL);

    free(tableInt);
}


/* Lit une ligne a l'entree standard
 * RES: renvoie une ligne de caracteres de taille quelconque lue sur stdin (sans '\n');
 *      renvoie NULL en cas d'erreur ou EOF.
 */
 // Pour une video sur cette fonction: http://youtu.be/Zuyhvnwmlao?hd=1
 char* lireLigne () {
    char buf[BUF_LEN];
    char* s = NULL;
    while (fgets(buf, BUF_LEN, stdin)) {
        int taille = strlen(buf);
        if (buf[strlen(buf)-1] == '\n') taille--;

        if (s == NULL) {
            s = (char*) malloc((taille+1) * sizeof(char));
            if (s == NULL) return NULL;
            strncpy(s,buf,taille);
        } else {
            s = (char*) realloc(s, (strlen(s)+taille+1) * sizeof(char));
            if (s == NULL) return NULL;
            strncat(s,buf,taille);
        }

        if (buf[strlen(buf)-1] == '\n')
            return s;
    }
    return NULL;
}

/* Affiche le contenu d'une table d'entiers
 * PRE: leg: chaine de caracteres representant la legende
 *      tab: table de sz nombres entiers
 * POST: affiche la legende leg puis le contenu de tab;
 *       affiche un message particulier si tab est vide
 */
void imprimerTable (char* leg , int* tab, int sz) {
    printf("\n%s\n", leg);
    if (sz == 0) {
        printf("\t[table vide]\n\n");
        return;
    }
    for (int* ptr=tab ; ptr < tab+sz; ptr++) {
        printf("\t%d\n", *ptr);
    }
    printf("\n");
}

/* Ajoute une valeur entiere a une table.
 * PRE: tab: pointeur vers une table d'entiers
 *      tailleL: nombre d'elements dans tab
 *      tailleP: taille physique de la tab (exprimee en nombre d'elements en memoire)
 *      n: entier a ajouter a la table
 * POST: n a ete ajoute a la table, tailleL incrementee et tailleP mise a jour;
 *       ajouterTable gere l'allocation dynamique de la table d'entiers:
 *       elle lui alloue de l'espace memoire lorsque la taille physique est nulle et
 *       lui realloue de la memoire lorsque tab est pleine.
 * RES: retourne VRAI si le traitement a ete correctement realise, FAUX en cas de souci
 */
 // Explications sur la signature (combien d'étoiles): https://youtu.be/7vpjEMquHaE
 // Explications sur l'algorithme: https://youtu.be/cX8DPJpwbfw
 
bool ajouterTable (int** tab, int* tailleL, int* tailleP, int n) {
    // Gestion de la place mémoire
    if (*tailleP == 0 || *tab == NULL){ 
        // table non allouee
        *tailleL = 0;
        *tailleP = DEFAULT_SIZE;
        if ((*tab = (int*)malloc(*tailleP*sizeof(int))) == NULL) {
            perror("ajouterTable: malloc ko");
            return false;
        }
    }
    else if (*tailleL == *tailleP){ 
	     // table pleine
        *tailleP *= 2;
        if ((*tab = (int*)realloc(*tab, *tailleP*sizeof(int))) == NULL) {
            perror("ajouterTable: realloc ko");
            return false;
        }
    }
    // Insertion dans la table
    (*tab)[*tailleL] = n;
    (*tailleL)++;
    return true;
}

/* Remplit une table d'entiers a partir d'une table de chaines
 * PRE: mots: table de nbrMots chaines de caracteres representant des entiers
 *      tab: pointeur vers une table d'entiers de taille physique tailleP
 * POST: remplit tab avec les chaines de mots converties en entiers
 *       et met a jour la taille physique tailleP de la table
 * RES: retourne la taille logique de la table ; -1 en cas d'erreur
 */
 // Explications: https://youtu.be/cX8DPJpwbfw
int chargerTable (char** mots, int nbrMots, int** tab, int* tailleP) {
    int tailleL = 0;
    for (int i = 0; i < nbrMots; i++) {
        if (!ajouterTable(tab, &tailleL, tailleP, atoi(mots[i]))) {
            fprintf(stderr, "chargerTable: erreur lors de l'ajout d'une valeur\n");
            return -1;
        }
    }
    return tailleL;
}
