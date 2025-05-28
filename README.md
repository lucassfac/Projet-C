traitement d'arbre genealogique

intructions de lancement :
Makefile1 : make -f Makefile1 puis ./testidentite
Makefile2 : make -f Makefile2 puis ./testgenea arbre10.ind arbre10.par
Makefile3 : make -f Makefile3 puis ./visuarbre arbre10.ind arbre10.par arbre10.dot puis cat arbre10.dot | dot -Tpdf > arbre10.pdf
Makefile4 : make -f Makefile4 puis ./visuarbreasc arbre10.ind arbre10.par 111 arbre10.dot puis cat arbre10.dot | dot -Tpdf > arbre10.pdf

instruction apres utilisation : nettoyer les objets executables avec make -f Makefile(n) clean (ou n represente l'indice du Makefile utilise) 
