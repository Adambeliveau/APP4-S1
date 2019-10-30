/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"
#include <stdlib.h>
#include <string.h>

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
	FILE * fPointer;
	char Premiere_ligne[MAX_CHAINE];
	char Deuxieme_ligne[MAX_CHAINE];
	char temporaire[MAX_CHAINE];
	int i = 0;
	int j = 0;
	int longueur;
	char valeur_Temp[MAX_CHAINE];
	int ligne_ou_colone = 0;
	int IsMeta = 0;
	
	fPointer = fopen(nom_fichier, "r");
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	fgets(Deuxieme_ligne, MAX_CHAINE, fPointer);
	
	longueur = strlen(Premiere_ligne);
	if((Deuxieme_ligne[0] == 'P' && Deuxieme_ligne[1] == '3') ||(Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '3'))
	{
		return 0;
	}
	
	if(Premiere_ligne[0] == '#' || (Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '2'))
	{
		if (Premiere_ligne[0] == '#')
		{
			IsMeta = 1;
			int element_Struct = 0;
			for (i = 1; i < longueur; i++)
			{
				if(element_Struct == 0 && Premiere_ligne[i] != ';')
				{
					p_metadonnees->auteur[i-1] = Premiere_ligne[i];
					printf("%s\n", p_metadonnees->auteur);
				}
				else if(element_Struct == 1 && Premiere_ligne[i] != ';')
				{  
					p_metadonnees->dateCreation[i-j-1] = Premiere_ligne[i];
					printf("%s\n", p_metadonnees->dateCreation);
				}
				else if(element_Struct == 2)
				{
					p_metadonnees->lieuCreation[i-j-1] = Premiere_ligne[i];
					printf("%s\n", p_metadonnees->lieuCreation);
				}
				else if(Premiere_ligne[i] == ';')
				{ 
					element_Struct++;
					j = i;
				}
				else
				{
					printf("***Erreur initialisation struct dans lire pgm***\n");
				}
			}
		}
		
		if(IsMeta == 0)
		{
			fseek(fPointer, 0, SEEK_SET);
			fgets(temporaire, MAX_CHAINE, fPointer);
		}
		fgets(temporaire, MAX_CHAINE, fPointer);
		longueur = strlen(temporaire);
		j = 1;
		for (i = 0; i < longueur; i++)
		{
			if(ligne_ou_colone == 0 && temporaire[i] != ' ')
			{
				valeur_Temp[i] = temporaire[i];
			}
			if(ligne_ou_colone == 1 && temporaire[i] != ' ')
			{ 
				valeur_Temp[i-j] = temporaire[i];
			}
			if(temporaire[i] == ' ' || i == longueur)
			{
				if(ligne_ou_colone == 1)
				{
					*p_colonnes = atoi(valeur_Temp);
				}
				else if(ligne_ou_colone == 0)
				{
					*p_lignes = atoi(valeur_Temp);
					j = i+1;
					ligne_ou_colone++;
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
	j = 0;
	i = 0;
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

