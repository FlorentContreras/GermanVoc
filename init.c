#include <stdio.h>
#include <stdlib.h>

#include "init.h"

int remplissage_general(Vocabulaire* ptr)
/* Fonction permettant de remplir la structure à partir de la DB */
{
    //ouvrir un fichier
    FILE* fichier = NULL;

    //ouverture du fichier
    fichier = fopen(nom_DB, "r+");

    int num_mot = 0;
    if (fichier != NULL)
    {
        // ne pas tenir compte de la premiere ligne qui comprend les titres
        saut_premiere_ligne(fichier);

        int sortie = 0;
        while(!sortie)
        {
            int av_struct = 0;
            int mot = 0;
            int carac = 0;

            // On boucle sur le nombre d'oeuvres
            while(av_struct < nbChampsStruct)
            {

                // lecture d'un caractère
                char temp;
                fscanf(fichier, "%c", &temp);

                if(temp=='$')
                {
                    av_struct = nbChampsStruct;
                    sortie = 1;
                    version(fichier);   // appelle de la fonction permettant de récupérer la derniere lecon et de l'affficher
                }
                else if(temp=='\n')
                {
                    // ne pas tenir compte de retour charriot de changement de ligne
                    num_mot++;
                }
                else if(temp=='\r' || temp==0x00)
                {
                    // ne rien faire
                }
                else if(temp==';')      // detection de la séparation des mots par le ';'
                {
                    remplissage_champs_interne(ptr, num_mot,'\0', carac, mot);    // on positionne un \0 à la suite des caractères
                    mot++;
                    carac = 0;
                    av_struct++ ;
                }
                else                    // on avance au caractère suivant
                {
                    remplissage_champs_interne(ptr, num_mot, temp, carac, mot);
                    carac++;
                }
            }
        }
    }
    else
    {
        printf("Impossible de trouver ou d'ouvrir le fichier %s\n", nom_DB);
    }

    // fermeture du fichier
    fclose(fichier);

    printf("Nombre de mots actuellement renseignees : %d\n\n", num_mot);

    return num_mot;
}

int remplissage_champs_interne(Vocabulaire* ptr_mot_a_remplir, int mot_en_cours ,char temp, int carac, int mot)
/* remplissage suivant l'avancement dans la structure */
{
    /* remplissage suivant l'avancement dans la structure */
    if(mot == 0)
    {
        (ptr_mot_a_remplir+mot_en_cours)->francais[carac] = temp;
    }
    else if(mot == 1)
    {
        (ptr_mot_a_remplir+mot_en_cours)->francais_2[carac] = temp;
    }
    else if(mot == 2)
    {
        (ptr_mot_a_remplir+mot_en_cours)->allemand[carac] = temp;
    }
    else if(mot == 3)
    {
        (ptr_mot_a_remplir+mot_en_cours)->allemand_2[carac] = temp;
    }
    else if(mot == 4)
    {
        (ptr_mot_a_remplir+mot_en_cours)->type[carac] = temp;
    }
    else if(mot == 5)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Genre[carac] = temp;
    }
    else if(mot == 6)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Singulier_1[carac] = temp;
    }
    else if(mot == 7)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Singulier_2[carac] = temp;
    }
    else if(mot == 8)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Singulier_3[carac] = temp;
    }
    else if(mot == 9)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Pluriel_1[carac] = temp;
    }
    else if(mot == 10)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Pluriel_2[carac] = temp;
    }
    else if(mot == 11)
    {
        (ptr_mot_a_remplir+mot_en_cours)->Pluriel_3[carac] = temp;
    }
    else if(mot >= nbChampsStruct)
    {
        printf("Au dela de la structure : %d\n", mot);
    }
    else
    {
        printf("Mot incompris : %d\n", mot);
    }

    return 0;
}

void version(FILE* fichier)
/* Permet de récupérer la date de la DB, et d'afficher la version du logiciel + de la DB*/
{
    char temp;
    int taille_lecon = 12;
    char lecon[taille_lecon];
    int erreur_date_DB = 0;

    for(int i = 0; i < nbChampsStruct; i++)
    // on se décalle à la fin des ;, au dela de la taille de la structure
    {
        fscanf(fichier, "%c", &temp);
        if(temp==0x00)
        {
            fscanf(fichier, "%c", &temp);
        }
    }

    for(int i = 0; i < taille_lecon - 1; i++)
    // recuperation de la date
    {
        fscanf(fichier, "%c", &temp);
        if(temp==0x00)
        {
            fscanf(fichier, "%c", &temp);
        }

        if(temp == '\n')            // en cas de date absente
        {
            erreur_date_DB = 1;
        }
        else
        {
            lecon[i] = temp;
        }
    }
    lecon[taille_lecon - 1] = '\0';   //ajout eof pour terminer le string

    if(!erreur_date_DB)
    {
        printf("Version du logiciel : %s \nVocabulaire jusqu'a : %s\n", _version, lecon);
    }
    else
    {
        printf("Version du logiciel : %s \n/!\\ Impossible de trouver la derniere lecon entree /!\\ \n", _version);
    }
}

void saut_premiere_ligne(FILE* fichier)
/* Permet de parcourir la première ligne du fichier sans l'interpreter (titres)*/
{
    int fin_de_ligne = 0;
    while(!fin_de_ligne)
    {
        // lecture d'un caractère
        char temp;
        fscanf(fichier, "%c", &temp);
        if(temp == '\n')
        {
            fin_de_ligne = 1;
        }
    }
}

