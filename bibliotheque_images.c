/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
    return OK;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
               int lignes, int colonnes, 
               int maxval, struct MetaData metadonnees)
{
    return OK;
}
int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	//copie des informations
	*p_lignes2=lignes1;
	*p_colonnes2=colonnes1;
	
	//copie de la matrice
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1; j++)
		{
			matrice2[i][j]=matrice1[i][j];
		}
	}
	//Verification 
	//if (pgm_sont_identiques(matrice1,lignes1,colonnes1,matrice2,*p_lignes2,*p_colonnes2)==OK)
		return OK;
	//else
		//return ERREUR;
}
int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
	int valeur;
	//Initialise toutes les valeurs de l'histogramme a 0
	for(int i=0;i<MAX_VALEUR+1;i++)
		histogramme[i]=0;
	
	//check combien de fois la couleur est utilisee
	for (int i = 0; i < lignes; i++)
	{
		for (int j= 0; j < colonnes; j++)
		{
			valeur=matrice[i][j];
			histogramme[valeur]++;	
		}
	}
	return OK;
}
int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	int couleur;
	int valeur=0;
	int choixCouleurs[MAX_VALEUR+1];
	pgm_creer_histogramme(matrice,lignes,colonnes,choixCouleurs);
	
	
	couleur=choixCouleurs[0];
	for (int i = 1; i <=MAX_VALEUR; i++)
	{
		if(valeur<=choixCouleurs[i]){
			couleur=i;
			valeur=choixCouleurs[i];
		}
	}
	return couleur;
}
int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	int valeurPixel;
	
	for(int i=0;i<lignes;i++)
	{
		for(int j=0;j<colonnes;j++)
		{
			valeurPixel=matrice[i][j];
			
			if(valeurPixel>maxval)
				return ERREUR;
			else
			{
				valeurPixel=maxval-valeurPixel;
				matrice[i][j]=valeurPixel;				
			}
		}
	}
	return OK;
}
int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	int verif=0;
	int nbLignes=lignes2-lignes1;
	int nbColonnes=colonnes2-colonnes1;
	int iLigne=0;
	int jColonne=0;
	
	p_lignes=&nbLignes;
	p_colonnes=&nbColonnes;
	
	int matriceExt[nbLignes][nbColonnes];
	
	//extraction de la matrice
	for(int i=lignes1;i<=lignes2;i++)
	{
		for(int j=colonnes1;j<=colonnes2;j++)
		{
			matriceExt[iLigne][jColonne]=matrice[i][j];
			jColonne++;	
		}
		iLigne++;
	}
	//superposition de la matrice extraite au coin superieur gauche
	for(int i=0;i<=nbLignes;i++)
	{
		for(int j=0;j<=nbColonnes;j++){
		
		}
	}

}

