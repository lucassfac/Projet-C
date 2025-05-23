#include <stdio.h>
#include "identite.h"


// A noter si vous voulez tester **IdentiteLiref** modifiez la ligne 17 avec le nom du fichier dont vous voulez tester
// Car on doit enlever les fichiers donnees
int main() {
    tIdentite id = IdentiteCreer(16, "MARTIN", "Jules", 'M', "12/13/2002");

    if (!id) {
        fprintf(stderr, "Erreur de création\n");
        return 1;
    }
    
    IdentiteAfficher(id);
    IdentiteLiberer(id);

    FILE *fichier = fopen("personne.ind", "r");   //lire indication avant de lancer dans le terminale
    if (fichier == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier personne.ind\n");
        return 1;
    }

    tIdentite identite = IdentiteLiref(fichier);
    if (identite == NULL) {
        fprintf(stderr, "Erreur de lecture de l'identité depuis le fichier\n");
        fclose(fichier);
        return 1;
    }

    IdentiteAfficher(identite);

    IdentiteLiberer(identite);

    fclose(fichier);

    return 0;
}
