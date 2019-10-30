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

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	FILE * fPointer;
	char Premiere_ligne[MAX_CHAINE];
	char Deuxieme_ligne[MAX_CHAINE];
	char temporaire[MAX_CHAINE];
	int i = 0;
	int j = 0;
	int longueur;
	int  IsMeta = 0;
	int Nb_Pixel = 0;
	int cpt_pixel = 0;
	
	fPointer = fopen(nom_fichier, "r");
	
	if(!fPointer)
	{
		return ERREUR_FICHIER;
	}
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	fgets(Deuxieme_ligne, MAX_CHAINE, fPointer);
	
	longueur = strlen(Premiere_ligne);
	if((Deuxieme_ligne[0] == 'P' && Deuxieme_ligne[1] != '2') ||(Premiere_ligne[0] == 'P' && Premiere_ligne[1] != '2') || (Premiere_ligne[0] != 'P' && Deuxieme_ligne[0] != 'P') || (Premiere_ligne[0] == 'P' && Deuxieme_ligne[0] == 'P'))
	{
		return ERREUR_FORMAT;
	}
	
	if(Premiere_ligne[0] == '#' || (Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '2'))
	{
		p_metadonnees->auteur[i] = '\0';
		p_metadonnees->lieuCreation[i] = '\0';
		p_metadonnees->dateCreation[i] = '\0';
		if (Premiere_ligne[0] == '#')
		{
			IsMeta = 1;
			int element_Struct = 0;
			for (i = 1; i < longueur; i++)
			{
				if(element_Struct == 0 && Premiere_ligne[i] != ';')
				{
					p_metadonnees->auteur[i-1] = Premiere_ligne[i];
					p_metadonnees->auteur[i] = '\0';
				}
				else if(element_Struct == 1 && Premiere_ligne[i] != ';')
				{  
					p_metadonnees->dateCreation[i-j-1] = Premiere_ligne[i];
					p_metadonnees->dateCreation[i-j] = '\0';
				}
				else if(element_Struct == 2)
				{
					p_metadonnees->lieuCreation[i-j-1] = Premiere_ligne[i];
					p_metadonnees->lieuCreation[i-j] = '\0';
				}
				else if(Premiere_ligne[i] == ';')
				{ 
					element_Struct++;
					j = i;
				}
				else
				{
					return ERREUR_FORMAT;
				}
			}
		}
		
		if(IsMeta == 0)
		{
			fseek(fPointer, 0, SEEK_SET);
			fgets(temporaire, MAX_CHAINE, fPointer);
		}
		fscanf(fPointer, "%d", p_lignes);
		
		if(*p_lignes == MAX_LARGEUR)
		{
			return ERREUR_TAILLE;
		} 
		 
		fscanf(fPointer, "%d", p_colonnes);
		
		if(*p_colonnes == MAX_HAUTEUR)
		{
			return ERREUR_TAILLE;
		}
		
		Nb_Pixel = *p_lignes * *p_colonnes;
		
		fscanf(fPointer, "%d", p_maxval);
	
	}
	i = 0;
	j = 0;
	while(!feof(fPointer))
	{
		cpt_pixel++;
		fscanf(fPointer, "%d", &matrice[j][i]);
		i++;
		if(i == *p_colonnes)
		{
			j++;
			i = 0;
		}
	}
	if(cpt_pixel != Nb_Pixel)
	{
		return ERREUR_FORMAT;
	}
	fclose(fPointer);
    return OK;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	FILE * fPointer;
	
	fPointer = fopen(nom_fichier, "w");
	
	if (!fPointer)
	{
		return ERREUR;
	}
	
	if(metadonnees.auteur[0] != '\0' || metadonnees.dateCreation[0] != '\0' || metadonnees.lieuCreation[0] != '\0')
	{
		fprintf(fPointer,"#%s;%s;%s",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
	}
	fprintf(fPointer,"P2\n");
	fprintf(fPointer,"%d %d\n",lignes,colonnes);
	fprintf(fPointer,"%d\n",maxval);
	for (int i = 0; i < colonnes; i++)
	{
		for(int j = 0 ; j < lignes ; j++)
		{
			fprintf(fPointer, "%d ",matrice[i][j]);
		}
		fprintf(fPointer, "\n");
	}
	
    return OK;
}

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	FILE * fPointer;
	char Premiere_ligne[MAX_CHAINE];
	char Deuxieme_ligne[MAX_CHAINE];
	char temporaire[MAX_CHAINE];
	int i = 0;
	int j = 0;
	int longueur;
	int  IsMeta = 0;
	int Nb_Pixel = 0;
	int cpt_pixel = 0;
	
	fPointer = fopen(nom_fichier, "r");
	
	if(!fPointer)
	{
		return ERREUR_FICHIER;
	}
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	fgets(Deuxieme_ligne, MAX_CHAINE, fPointer);
	
	longueur = strlen(Premiere_ligne);
	if((Deuxieme_ligne[0] == 'P' && Deuxieme_ligne[1] != '3') ||(Premiere_ligne[0] == 'P' && Premiere_ligne[1] != '3') || (Premiere_ligne[0] != 'P' && Deuxieme_ligne[0] != 'P') || (Premiere_ligne[0] == 'P' && Deuxieme_ligne[0] == 'P'))
	{
		printf("0");
		return ERREUR_FORMAT;
	}
	
	if(Premiere_ligne[0] == '#' || (Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '2'))
	{
		p_metadonnees->auteur[i] = '\0';
		p_metadonnees->lieuCreation[i] = '\0';
		p_metadonnees->dateCreation[i] = '\0';
		if (Premiere_ligne[0] == '#')
		{
			IsMeta = 1;
			int element_Struct = 0;
			for (i = 1; i < longueur; i++)
			{
				if(element_Struct == 0 && Premiere_ligne[i] != ';')
				{
					p_metadonnees->auteur[i-1] = Premiere_ligne[i];
					p_metadonnees->auteur[i] = '\0';
				}
				else if(element_Struct == 1 && Premiere_ligne[i] != ';')
				{  
					p_metadonnees->dateCreation[i-j-1] = Premiere_ligne[i];
					p_metadonnees->dateCreation[i-j] = '\0';
				}
				else if(element_Struct == 2)
				{
					p_metadonnees->lieuCreation[i-j-1] = Premiere_ligne[i];
					p_metadonnees->lieuCreation[i-j] = '\0';
				}
				else if(Premiere_ligne[i] == ';')
				{ 
					element_Struct++;
					j = i;
				}
				else
				{
					printf("1");
					return ERREUR_FORMAT;
				}
			}
		}
		
		if(IsMeta == 0)
		{
			fseek(fPointer, 0, SEEK_SET);
			fgets(temporaire, MAX_CHAINE, fPointer);
		}
		fscanf(fPointer, "%d", p_lignes);
		
		if(*p_lignes == MAX_LARGEUR)
		{
			return ERREUR_TAILLE;
		} 
		 
		fscanf(fPointer, "%d", p_colonnes);
		
		if(*p_colonnes == MAX_HAUTEUR)
		{
			return ERREUR_TAILLE;
		}
		
		Nb_Pixel = *p_lignes * *p_colonnes ;
		
		fscanf(fPointer, "%d", p_maxval);
	
	}
	i = 0;
	j = 0;
	while(!feof(fPointer))
	{
		cpt_pixel++;
		fscanf(fPointer, "%d", &matrice[j][i].valeurR);
		fscanf(fPointer, "%d", &matrice[j][i].valeurG);
		fscanf(fPointer, "%d", &matrice[j][i].valeurB);
		i++;
		if(i == *p_colonnes)
		{
			j++;
			i = 0;
		}
	}
	if(cpt_pixel != Nb_Pixel)
	{
		return ERREUR_FORMAT;
	}
	fclose(fPointer);
    return OK;
}
int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	FILE * fPointer;
	
	fPointer = fopen(nom_fichier, "w");
	
	if (!fPointer)
	{
		return ERREUR;
	}
	
	if(metadonnees.auteur[0] != '\0' || metadonnees.dateCreation[0] != '\0' || metadonnees.lieuCreation[0] != '\0')
	{
		fprintf(fPointer,"#%s;%s;%s",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
	}
	fprintf(fPointer,"P2\n");
	fprintf(fPointer,"%d %d\n",lignes,colonnes);
	fprintf(fPointer,"%d\n",maxval);
	for (int i = 0; i < colonnes; i++)
	{
		for(int j = 0 ; j < lignes ; j++)
		{
			fprintf(fPointer, "%d ",matrice[i][j].valeurR);
			fprintf(fPointer, "%d ",matrice[i][j].valeurG);
			fprintf(fPointer, "%d ",matrice[i][j].valeurB);
		}
		fprintf(fPointer, "\n");
	}
	
    return OK;
}
	

