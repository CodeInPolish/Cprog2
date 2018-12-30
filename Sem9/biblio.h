#ifndef _BIBLIO_H_
#define _BIBLIO_H_

typedef enum {BD, PO, TH, RO, RH, LF, LE, SC, IN, SF, SA, HI} Genre;

typedef struct Livre{
	char titre[129];
	char auteur[80];
	long ISBN;
	char editeur[50];
	int annee;
	Genre genre;
}Livre;

int lireLivre();
char* livre2str();
void afficherBib();
int ajouterLivre();
int str2genre();
char* genre2str(int);
int comparerLivre();

#endif