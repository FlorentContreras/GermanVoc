#include <stdio.h>
#include <stdlib.h>

#include "main.h"

typedef struct
{
    char francais[taille_entrant];
    char francais_2[taille_entrant];
    char allemand[taille_entrant];
    char allemand_2[taille_entrant];
    char type[taille_entrant];
    char Genre[taille_entrant];
    char Singulier_1[taille_entrant];
    char Singulier_2[taille_entrant];
    char Singulier_3[taille_entrant];
    char Pluriel_1[taille_entrant];
    char Pluriel_2[taille_entrant];
    char Pluriel_3[taille_entrant];

} Vocabulaire;

int remplissage_general(Vocabulaire*);
int remplissage_champs_interne(Vocabulaire*, int, char, int, int);
void version(FILE*);
void saut_premiere_ligne(FILE*);

