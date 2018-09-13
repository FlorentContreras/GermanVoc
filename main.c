#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "init.h"
#include "affichage.h"

int main()
{
    Vocabulaire* ptr_voc;
    int nombre_de_mots = 50000;   // init de nombre large, ramené au nombre de mots réels ensuite

    ptr_voc = (Vocabulaire*) malloc(nombre_de_mots * sizeof(Vocabulaire));

    //remplissage de la structure par le fichier DB
    nombre_de_mots = remplissage_general(ptr_voc);

    // affichage des mots
    affichage_alleatoire(ptr_voc, nombre_de_mots);

    free(ptr_voc);
    return 0;
}
