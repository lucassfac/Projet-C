#include "genea.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s fichier.ind fichier.par\n", argv[0]);
        return 1;
    }

    // Lire et ajouter toutes les personnes
    tArbre Arbre = ArbreLirePersonnesFichier(argv[1]);

    // Lire et ajouter les liens de parenté
    Arbre = ArbreLireLienParenteFichier(Arbre, argv[2]);

    // Afficher l'arbre généalogique
    ArbreAfficher(Arbre);

    // Libérer l'arbre
    ArbreLiberer(Arbre);

    return 0;
}