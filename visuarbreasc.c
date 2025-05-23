#include "genea.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Utilisation: %s fichier.ind fichier.par identifiant fichier.dot\n", argv[0]);
        return 1;
    }

    tArbre Arbre = ArbreLirePersonnesFichier(argv[1]);
    Arbre = ArbreLireLienParenteFichier(Arbre, argv[2]);

    int Identifiant = atoi(argv[3]);
    ArbreAfficherAscendants(Arbre, Identifiant);
    ArbreEcrireAscendantsGV(Arbre, Identifiant, argv[4]);
    ArbreLiberer(Arbre);

    return 0;
}
