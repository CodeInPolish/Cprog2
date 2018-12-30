#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#define MAX_TITRE 128
#define MAX_AUTEUR 80
#define MAX_EDITEUR 50
#define MAX_ISBN 13
#define MAX_ANNEE 4
#define MAX_GENRE 21
#define MAX_STR MAX_TITRE+MAX_AUTEUR+MAX_EDITEUR+MAX_ISBN+MAX_ANNEE+MAX_GENRE+6

typedef enum {BD, PO, TH, RO, RH, LF, LE, SC, IN, SF, SA, HI} Genre;

typedef enum {TITRE, AUTEUR, ISBN, EDITEUR, ANNEE, GENRE} InfoLivre;

typedef struct {
	char titre[MAX_TITRE+1];
	char auteur[MAX_AUTEUR+1];
	long isbn;
	char editeur[MAX_EDITEUR+1];
	int annee;
	Genre genre;
}Livre;

bool lireLivre(Livre* l);
char* livre2str(Livre l);
void afficherBib(Livre* tab);
int ajouterLivre(Livre** tab, Livre livre, int* logSize, int* physSize);
Genre str2genre(char* str);
char* genre2str(Genre g);
int comparerLivre(Livre l1, Livre l2);

#endif