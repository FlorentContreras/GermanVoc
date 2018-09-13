#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "init.h"
#include "affichage.h"

void affichage(Vocabulaire* ptr_mot_a_afficher, int nombre_mots)
/* Affichage de la structure */
{
    for(int i = 0; i < nombre_mots; ++i)
    {
        printf("%s : %s \n", (ptr_mot_a_afficher+i)->francais, (ptr_mot_a_afficher+i)->allemand);

    }
}

void affichage_alleatoire(Vocabulaire* ptr_mot_a_afficher, int nombre_mots)
/* Affichage d'un mot aleatoirement */
{
    int liste[nombre_mots];
    char temp[50];
    strcpy(temp, "mot-a-trouver");
    for(int i = 0; i < nombre_mots; i++)
    {
        liste[i] = i;
    }
    // rendre l'ordre de sortie alleatoire
    tri_alleatoire(liste, nombre_mots);

    int i = 0;
    int mot_suivant;

    while(i < nombre_mots)
    {
        // Ne prend pas en compte les noms
        i = saut_noms(ptr_mot_a_afficher, liste, i);

        mot_suivant = 0;
        while(!mot_suivant)
        {
            if(!strcmp(temp, (ptr_mot_a_afficher+liste[i])->allemand))
            {
                printf("bravo !!!\n**************************************** \n\n");
                i++;
                mot_suivant = 1;
            }
            else if(!strcmp(temp, "1"))
            {
                printf("Resultat attendu : %s\n**************************************** \n\n", (ptr_mot_a_afficher+liste[i])->allemand);
                i++;
                mot_suivant = 1;
                strcpy(temp, "mot-a-trouver");

            }
            else if(!strcmp(temp, "2"))
            {
                printf("Resultat attendu : %s\n**************************************** \n\n", (ptr_mot_a_afficher+liste[i])->allemand);
                i = nombre_mots;
                mot_suivant = 1;
            }
            else
            {
                printf("(%d / %d)\nTraduire le mot : %s \n(pour voir la reponse taper 1, pour sortir taper 2)\nReponse : ", i, nombre_mots, (ptr_mot_a_afficher+liste[i])->francais);
                scanf("%s", temp);
            }
        }

    }
}

int tri_alleatoire(int * tableau_a_trier, int taille_a_trier)
/* Permet de trier alleatoirement */
{
	int nombre_tire=0;
	int temp=0;
	// initialisatoin de la fonction randum sur l'heure (en seconde)
	srand(time(NULL));

	for(int i = 0; i < taille_a_trier ; i++)
	{
		nombre_tire = rand_a_b(0,taille_a_trier);

		// On échange les contenus des cases i et nombre_tire
		temp = tableau_a_trier[i];
		tableau_a_trier[i] = tableau_a_trier[nombre_tire];
		tableau_a_trier[nombre_tire]=temp;
	}

	return 0;
}

int rand_a_b(int a, int b)
/* renvoie une valeur alleatoire entre a et b */
{
    return rand()%(b-a) + a;
}

int saut_noms(Vocabulaire * ptr_mot_a_trier, int * liste, int i)
/* Si le mot est un nom, on le l'affiche pas */
{
    while(!strcmp("nom", (ptr_mot_a_trier+liste[i])->type))
    {
        i++;
    }
    return i;
}
