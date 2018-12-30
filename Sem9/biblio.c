#include "biblio.h"

#define NB_CHAMP 6

bool lireLivre(Livre* l){
	bool complete = false;
	char ligne[MAX_TITRE+2];
	for(InfoLivre i=0;i<NB_CHAMP;i++){
		fgets(ligne, MAX_TITRE+2, stdin);
		int len = strlen(ligne)-1;
		ligne[len] = '\0';

		switch(i){
			case TITRE:
				strncpy(l->titre, ligne, len);
				break;
			case AUTEUR:
				strncpy(l->auteur, ligne, len);
				break;
			case ISBN:
				l->isbn = strtol(ligne, NULL, 10);
				break;
			case EDITEUR:
				strncpy(l->editeur, ligne, len);
				break;
			case ANNEE:
				l->annee = (int) strtol(ligne, NULL, 10);
				break;
			case GENRE:
				l->genre = str2genre(ligne);
				complete=true;
				break;
		}
	}

	fgets(ligne, MAX_TITRE+2, stdin);
	if(strlen(ligne)>1){
		return false;
	}
	else{
		return complete;
	}
}

char* livre2str(Livre l){
	char str[308];
	for(InfoLivre i=0;i<NB_CHAMP;i++){
		switch(i){
			case TITRE:
				strncat(str, l.titre, MAX_TITRE);
				break;
			case AUTEUR:
				strncat(str, l.auteur, MAX_AUTEUR);
				break;
			case ISBN:
				;
				char buffer1[MAX_ISBN+1];
				sprintf(buffer1, "%ld", l.isbn);
				strncat(str, buffer1, MAX_ISBN);
				break;
			case EDITEUR:
				strncat(str, l.editeur, MAX_EDITEUR);
				break;
			case ANNEE:
				;
				char buffer2[MAX_ANNEE+1];
				sprintf(buffer2, "%d", l.annee);
				strncat(str, buffer2, MAX_ANNEE);
				break;
			case GENRE:
				strncat(str, genre2str(l.genre), MAX_GENRE);
				break;
		}
	return str;
}

void afficherBib(Livre* tab){

}

int ajouterLivre(Livre** tab, Livre l, int* logSize, int* physSize){
	return 0;
}

Genre str2genre(char* str){
	Genre g=0;
	return g;
}

char* genre2str(Genre g){
	return (char) "n'imp";
}

int comparerLivre(Livre l1, Livre l2){
	return 0;
}