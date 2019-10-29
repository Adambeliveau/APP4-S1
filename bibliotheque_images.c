/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"
#include <stdlib.h>

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
	FILE * fPointer;
	char Premiere_ligne[MAX_CHAINE];
	char * temporaire = NULL;
	int i = 0;
	int j = 0;
	
	fPointer = fopen(nom_fichier, "r");
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	
	if(Premiere_ligne[0] == '#' || (Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '2'))
	{
		if (Premiere_ligne[0] == '#')
		{
			int element_Struct = 0;
			for (i = 1; i < MAX_CHAINE; i++)
			{
				if(element_Struct == 0 && Premiere_ligne[i] != ';')
				{
					p_metadonnees->auteur[i-1] = Premiere_ligne[i];
				}
				else if(element_Struct == 1 && Premiere_ligne[i] != ';')
				{
					p_metadonnees->dateCreation[i-1] = Premiere_ligne[i];
				}
				else if(element_Struct == 2 && (Premiere_ligne[i] != ';' || Premiere_ligne[i] != '\0'))
				{
					p_metadonnees->lieuCreation[i-1] = Premiere_ligne[i];
				}
				else if(Premiere_ligne[i] == '\0')
				{
					break;
				}
				else if(Premiere_ligne[i] == ';')
				{ 
					element_Struct++;
				}
				else
				{
					printf("***Erreur initialisation struct dans lire pgm***\n");
				}
			}
		}
		
		if(Premiere_ligne[1] == '2')
		{
			char * valeur_Temp = NULL;
			
			fseek(fPointer, 2, SEEK_SET);
			fgets(temporaire, MAX_CHAINE, fPointer);
			for (i = 0; i < MAX_CHAINE; i++)
			{
				int ligne_ou_colone = 0;
				int j = 0;
				if(ligne_ou_colone == 0 && temporaire[i] != ' ')
				{
					valeur_Temp[i] = temporaire[i];
				}
				else if(ligne_ou_colone == 1 && temporaire[i] != ' ')
				{ 
					valeur_Temp[i-j] = temporaire[i];
				}
				else if(temporaire[i] == ' ')
				{
					if (ligne_ou_colone == 0)
					{
						*p_lignes = atoi(valeur_Temp);
						j = i;
					}
					if(ligne_ou_colone == 1)
					{
						*p_colonnes = atoi(valeur_Temp);
						break;
					}
				}
				
			}
			fgets(temporaire, MAX_CHAINE, fPointer);
			for (i = 0; i < MAX_CHAINE; i++)
			{
				if (temporaire[i] != ' ')
				{
					valeur_Temp[i] = temporaire[i];
				}
				else if(temporaire[i] == ' ')
				{
					*p_maxval = atoi(valeur_Temp);
				}
			}
		}
	}
	
	while(!feof(fPointer))
	{
		fscanf(fPointer, "%d", &matrice[i][j]);
		i++;
		if(i == *p_lignes)
		{
			j++;
			i = 0;
		}
	}
	fclose(fPointer);
    return OK;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
               int lignes, int colonnes, 
               int maxval, struct MetaData metadonnees)
{
    return OK;
}

