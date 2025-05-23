#ifndef GENEA_H
#define GENEA_H

#include "identite.h"

struct sFiche {
    tIdentite Identite;
    struct sFiche *pPere;
    struct sFiche *pMere;
    struct sFiche *pSuivante;
};

struct sArbre {
    struct sFiche *pPremiere;
    struct sFiche *pDerniere;
};

typedef struct sArbre *tArbre;

extern tArbre ArbreCreer(void);
extern void ArbreAfficher(tArbre Arbre);
extern void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite);
extern void ArbreLiberer(tArbre Arbre);
extern tArbre ArbreLirePersonnesFichier(char Fichier[]);
extern void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente);
extern int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente);
extern tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]);
extern void ArbreEcrireGV(tArbre Arbre, char Fichier[]);
extern void ArbreAfficherAscendants(tArbre Arbre, int Identifiant);
extern void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]);
extern void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]);

#endif // GENEA_H
