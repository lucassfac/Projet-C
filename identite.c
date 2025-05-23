#include "identite.h"
#include <stdlib.h>
#include <stdio.h>

static int longueur_chaine(const char *s) {
    int len = 0;
    while (s[len] != '\0' && s[len] != '\n'){ 
        len++;
    }
    return len;
}

static void copier_chaine(char *dest, const char *src, int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

tIdentite IdentiteCreer(int Id, char *Nom, char *Prenom, char Sexe, char DateNais[]) {
    tIdentite id = malloc(sizeof(struct sIdentite));
    if (id == NULL){
        printf("probleme d'allocation d'une nouvelle struct \n");
        return NULL;
    }

    int lenNom = longueur_chaine(Nom);
    int lenPrenom = longueur_chaine(Prenom);

    id->Nom = malloc(lenNom + 1);
    if (id->Nom == NULL) {
        free(id);
        return NULL;
    }
    copier_chaine(id->Nom, Nom, lenNom);

    id->Prenom = malloc(lenPrenom + 1);
    if (id->Prenom == NULL) {
        free(id->Nom);
        free(id);
        return NULL;
    }
    copier_chaine(id->Prenom, Prenom, lenPrenom);

    id->Identifiant = Id;
    id->Sexe = Sexe;

    for (int i = 0; i < LG_DATE; i++) {
        id->DateNaissance[i] = DateNais[i];
    }
    id->DateNaissance[LG_DATE] = '\0';

    return id;
}

int IdentiteIdentifiant(tIdentite Identite){
    return Identite->Identifiant;
}

char *IdentiteNom(tIdentite Identite){
    return Identite->Nom;
}

char *IdentitePrenom(tIdentite Identite){
    return Identite->Prenom;
}

char IdentiteSexe(tIdentite Identite){
    return Identite->Sexe;
}

char *IdentiteDateNaissance(tIdentite Identite){
    return Identite->DateNaissance;
}

void IdentiteAfficher(tIdentite Identite){
    int Id = IdentiteIdentifiant(Identite);
    char *Nom = IdentiteNom(Identite);
    char *Prenom = IdentitePrenom(Identite);
    char Sexe = IdentiteSexe(Identite);
    char *Date = IdentiteDateNaissance(Identite);
    printf("[%d] %s %s, %c, %s\n", Id, Nom, Prenom, Sexe, Date);
}

void IdentiteLiberer(tIdentite Identite) {
    if(Identite != NULL){
        free(Identite->Nom);
        free(Identite->Prenom);
        free(Identite);
    }
} 

tIdentite IdentiteLiref(FILE *f) {
    int Id;
    char Nom[81], Prenom[81], Sexe, DateNais[LG_DATE + 1];

    if (fscanf(f, "%d\n%80s\n%80s\n%c\n%10s\n", &Id, Nom, Prenom, &Sexe, DateNais) == 5) {
        tIdentite nouvelleIdentite = IdentiteCreer(Id, Nom, Prenom, Sexe, DateNais);
        return nouvelleIdentite;
    }
    return NULL;
}
