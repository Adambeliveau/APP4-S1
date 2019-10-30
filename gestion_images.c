/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
   // int histogramme[MAX_VALEUR+1];
   // char nom[MAX_CHAINE];
    struct MetaData metadonnees;
    int Retour_Fonction;


    printf("-> Debut!\n");

    
    //Sherbrooke_Frontenac_nuit.pgm
    //Sherbrooke_Frontenac_nuit.ppm
    //TEST.txt
	Retour_Fonction = pgm_lire("TEST.txt", image1, &lignes1, &colonnes1, &maxval, &metadonnees);
	if(Retour_Fonction == -3)
	{
		printf("Erreur Format\n");
	}
	else if(Retour_Fonction == -2)
	{
		printf("Erreur taille\n");
	}
	else if(Retour_Fonction == -1)
	{
		printf("Erreur Fichier\n");
	}
	else
	{
		printf("ligne\tcolonne\tmaxval\tauteur\tdateCreation\tlieuCreation\n");
		printf("%d\t%d\t%d\t%s\t%s\t%s\n", lignes1, colonnes1,maxval,metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
	}
	
	Retour_Fonction = pgm_ecrire("allolemonde.txt", image1, lignes1, colonnes1, maxval, metadonnees);
	if(Retour_Fonction == 1)
	{
		printf("Erreur\n");
	}
	else
	{
		printf("GOOD\n");
	}
	
	Retour_Fonction = ppm_lire("TESTRGB.txt", imageRGB1, &lignes2, &colonnes2, &maxval, &metadonnees);
	if(Retour_Fonction == -3)
	{
		printf("Erreur Format\n");
	}
	else if(Retour_Fonction == -2)
	{
		printf("Erreur taille\n");
	}
	else if(Retour_Fonction == -1)
	{
		printf("Erreur Fichier\n");
	}
	else
	{
		printf("ligne\tcolonne\tmaxval\tauteur\tdateCreation\tlieuCreation\n");
		printf("%d\t%d\t%d\t%s\t%s\t%s\n", lignes2, colonnes2, maxval, metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
	}
	
	Retour_Fonction = ppm_ecrire("allolemondeRGB.txt", imageRGB1, lignes2, colonnes2, maxval, metadonnees);
	if(Retour_Fonction == 1)
	{
		printf("Erreur\n");
	}
	else
	{
		printf("GOOD\n");
	}
	
	/*printf("\n-> Fin!\n");
	for (int i = 0; i < lignes1; i++)
	{
		for(int j = 0; j < colonnes1;j++)
		{
			printf("%d\t",imageRGB1[i][j].valeurR);
			printf("%d\t",imageRGB1[i][j].valeurG);
			printf("%d\t",imageRGB1[i][j].valeurB);
		}
		printf("\n");
	}*/

    return 0;
}
