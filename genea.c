#include "genea.h"

tArbre ArbreCreer(void) {
    tArbre nouvelArbre = malloc(sizeof(struct sArbre));
    if (nouvelArbre == NULL) {
        return NULL;
    }
    nouvelArbre->pPremiere = NULL;
    nouvelArbre->pDerniere = NULL;
    return nouvelArbre;
}

void ArbreAfficher(tArbre Arbre) {
    struct sFiche *fiche = Arbre->pPremiere;
    while (fiche != NULL) {
        IdentiteAfficher(fiche->Identite);
        printf("\tPère : ");
        if (fiche->pPere != NULL) {
            IdentiteAfficher(fiche->pPere->Identite);
        } else {
            printf("inconnu\n");
        }
        printf("\tMère : ");
        if (fiche->pMere != NULL) {
            IdentiteAfficher(fiche->pMere->Identite);
        } else {
            printf("inconnue\n");
        }
        fiche = fiche->pSuivante;
    }
}

void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite) {
    struct sFiche *nouvelleFiche = malloc(sizeof(struct sFiche));
    if (nouvelleFiche == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
    nouvelleFiche->Identite = Identite;
    nouvelleFiche->pPere = NULL;
    nouvelleFiche->pMere = NULL;
    nouvelleFiche->pSuivante = NULL;

    if (Arbre->pDerniere == NULL) {
        Arbre->pPremiere = nouvelleFiche;
    } else {
        Arbre->pDerniere->pSuivante = nouvelleFiche;
    }
    Arbre->pDerniere = nouvelleFiche;
}


void ArbreLiberer(tArbre Arbre) {
    struct sFiche *fiche = Arbre->pPremiere;
    while (fiche != NULL) {
        struct sFiche *suivante = fiche->pSuivante;
        IdentiteLiberer(fiche->Identite);
        free(fiche);
        fiche = suivante;
    }
    free(Arbre);
}

tArbre ArbreLirePersonnesFichier(char Fichier[]) {
    FILE *f = fopen(Fichier, "r");
    if (f == NULL) {
        return NULL;
    }

    tArbre Arbre = ArbreCreer();
    tIdentite Identite;
    while ((Identite = IdentiteLiref(f)) != NULL) {
        ArbreAjouterPersonne(Arbre, Identite);
    }
    fclose(f);
    return Arbre;
}


void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente) {
    struct sFiche *fiche = Arbre->pPremiere;
    struct sFiche *enfant = NULL, *parent = NULL;

    while (fiche != NULL) {
        if (IdentiteIdentifiant(fiche->Identite) == IdEnfant) {
            enfant = fiche;
        }
        if (IdentiteIdentifiant(fiche->Identite) == IdParent) {
            parent = fiche;
        }
        fiche = fiche->pSuivante;
    }

    if (enfant == NULL) {
        fprintf(stderr, "Erreur : enfant avec identifiant %d non trouvé\n", IdEnfant);
        return;
    }
    if (parent == NULL) {
        fprintf(stderr, "Erreur : parent avec identifiant %d non trouvé\n", IdParent);
        return;
    }

    if (Parente == 'P') {
        enfant->pPere = parent;
    } else if (Parente == 'M') {
        enfant->pMere = parent;
    }
}

int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente) {
    if (fscanf(f, "%d %d %c\n", pIdEnfant, pIdParent, pParente) == 3) {
        return 1;
    }
    return 0;
}

tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]) {
    FILE *f = fopen(Fichier, "r");
    if (f == NULL) {
        return NULL;
    }

    int IdEnfant, IdParent;
    char Parente;
    while (ArbreLireLienParentef(f, &IdEnfant, &IdParent, &Parente)) {
        ArbreAjouterLienParente(Arbre, IdEnfant, IdParent, Parente);
    }
    fclose(f);
    return Arbre;
}
static void EcrirePere(FILE *f, struct sFiche *fiche){
    while (fiche != NULL) {
        if(IdentiteSexe(fiche->Identite) == 'M'){
            fprintf(f, "    %d [label=\"%s\\n%s\\n%s\"];\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteNom(fiche->Identite),
                IdentitePrenom(fiche->Identite),
                IdentiteDateNaissance(fiche->Identite));
            fiche = fiche->pSuivante;
        }
        else{
            fiche = fiche->pSuivante;
        }
    }
}
static void EcrireMere(FILE *f, struct sFiche *fiche){
    while (fiche != NULL) {
        if(IdentiteSexe(fiche->Identite) == 'F'){
            fprintf(f, "    %d [label=\"%s\\n%s\\n%s\"];\n",
                IdentiteIdentifiant(fiche->Identite),
                IdentiteNom(fiche->Identite),
                IdentitePrenom(fiche->Identite),
                IdentiteDateNaissance(fiche->Identite));
            fiche = fiche->pSuivante;
        }
        else{
            fiche = fiche->pSuivante;
        }
    }
}

static void EcrireLien(FILE *f, struct sFiche *fiche){
    while (fiche != NULL) {
        if (fiche->pPere != NULL) {
            fprintf(f, "    %d -> %d;\n",
                    IdentiteIdentifiant(fiche->Identite),
                    IdentiteIdentifiant(fiche->pPere->Identite));
        }
        if (fiche->pMere != NULL) {
            fprintf(f, "    %d -> %d;\n",
                    IdentiteIdentifiant(fiche->Identite),
                    IdentiteIdentifiant(fiche->pMere->Identite));
        }
        fiche = fiche->pSuivante;
    }
}
void ArbreEcrireGV(tArbre Arbre, char Fichier[]){
    FILE *f = fopen(Fichier,"w");
    if(f == NULL){
        return;
    }

    fprintf(f,"digraph {\n");
    fprintf(f,"    rankdir = \"BT\";\n");
    fprintf(f,"\n");
    fprintf(f,"    node [shape=box,color=blue,fontname=\"Arial\",fontsize=10];\n");

    struct sFiche *fiche = Arbre->pPremiere;
    EcrirePere(f, fiche);

    fprintf(f,"\n");
    fprintf(f,"    node [color=green];\n" );
    
    fiche = Arbre->pPremiere;
    EcrireMere(f ,fiche);

    fprintf(f,"\n");
    fprintf(f,"    edge [dir=none];\n");

    fiche = Arbre->pPremiere;
    EcrireLien(f, fiche);

    fprintf(f, "}\n");
    fclose(f);
    return;
}

//fonction complement ArbreAfficherAscendants
static void ArbreAfficherAscendantsRec(struct sFiche *fiche, int niveau) {
    IdentiteAfficher(fiche->Identite);
    if (fiche->pPere != NULL) {
        for (int i = 0; i < niveau; i++) {
            printf("\t");
        }
        printf("Père : ");
        ArbreAfficherAscendantsRec(fiche->pPere, niveau + 1);
    }
    if (fiche->pMere != NULL) {
        for (int i = 0; i < niveau; i++) {
            printf("\t");
        }
        printf("Mère : ");
        ArbreAfficherAscendantsRec(fiche->pMere, niveau + 1);
    }
}

void ArbreAfficherAscendants(tArbre Arbre, int Identifiant) {
    struct sFiche *fiche = Arbre->pPremiere;
    while (fiche != NULL) {
        if (IdentiteIdentifiant(fiche->Identite) == Identifiant) {
            ArbreAfficherAscendantsRec(fiche, 0);
            return;
        }
        fiche = fiche->pSuivante;
    }
    fprintf(stderr, "Erreur : personne avec identifiant %d non trouvée\n", Identifiant);
}

//fonctions auxiliaires de ArbreEcrireAscendantsGV
static void ArbreEcrireAscendantsGVRecNoeud(FILE *f, struct sFiche *fiche) {
    if (fiche == NULL){
        return;
    }
    

    fprintf(f, "    node [color=%s];\n",
        IdentiteSexe(fiche->Identite) == 'M' ? "blue" : "green");
    fprintf(f,"\n");
    fprintf(f, "    %d [label=\"%s\\n%s\\n%s\"];\n",
        IdentiteIdentifiant(fiche->Identite),
        IdentiteNom(fiche->Identite),
        IdentitePrenom(fiche->Identite),
        IdentiteDateNaissance(fiche->Identite));

    
    ArbreEcrireAscendantsGVRecNoeud(f, fiche->pPere);
    ArbreEcrireAscendantsGVRecNoeud(f, fiche->pMere);
}

static void ArbreEcrireAscendantsGVRecLien(FILE *f, struct sFiche *fiche) {
    if (fiche == NULL){
        return;
    }

    ArbreEcrireAscendantsGVRecLien(f, fiche->pPere);
    ArbreEcrireAscendantsGVRecLien(f, fiche->pMere);

    if (fiche->pPere != NULL) {
        fprintf(f, "    %d -> %d;\n",
            IdentiteIdentifiant(fiche->Identite),
            IdentiteIdentifiant(fiche->pPere->Identite));
    }

    if (fiche->pMere != NULL) {
        fprintf(f, "    %d -> %d;\n",
            IdentiteIdentifiant(fiche->Identite),
            IdentiteIdentifiant(fiche->pMere->Identite));
    }
}

void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]) {
    FILE *f = fopen(Fichier, "w");
    if (f == NULL) {
        return;
    }

    fprintf(f, "digraph {\n");
    fprintf(f, "    rankdir=\"BT\";\n");
    fprintf(f,"\n");
    fprintf(f, "    node [shape=box,fontname=\"Arial\",fontsize=10];\n");
    fprintf(f,"\n");
    fprintf(f, "    edge [dir=none];\n");

    struct sFiche *fiche = Arbre->pPremiere;
    while (fiche != NULL) {
        int trouve = 1;
        if (IdentiteIdentifiant(fiche->Identite) == Identifiant && trouve == 1) {
            ArbreEcrireAscendantsGVRecNoeud(f, fiche);
            ArbreEcrireAscendantsGVRecLien(f, fiche);
            trouve = 0;
        }
        fiche = fiche->pSuivante;
    }

    fprintf(f, "}\n");
    fclose(f);
}