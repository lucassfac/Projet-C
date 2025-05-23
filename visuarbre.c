#include "genea.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Utilisation: %s fichier.ind fichier.par fichier.dot\n", argv[0]);
        return 1;
    }

    tArbre Arbre = ArbreLirePersonnesFichier(argv[1]);
    Arbre = ArbreLireLienParenteFichier(Arbre, argv[2]);

    ArbreEcrireGV(Arbre, argv[3]);
    ArbreLiberer(Arbre);

    return 0;
}

