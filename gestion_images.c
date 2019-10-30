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
    int lignes1=3;
    int colonnes1=3;
    int lignes2=0;
    int colonnes2=0;
    int *plignes2,*pcolonnes2;
    int val=4;
    //int maxval;
    //int histogramme[MAX_VALEUR+1];
    //char nom[MAX_CHAINE];
    //struct MetaData metadonnees;

	plignes2=&lignes2;
	pcolonnes2=&colonnes2;
	int retour;
	
	printf("Image1:\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			image1[i][j]=i+j;
			printf("%d ",image1[i][j]);
		}
		printf("\n");
	}
	
	retour=pgm_copier(image1,lignes1,colonnes1,image2,plignes2,pcolonnes2);
	
	printf("Copie: %d\n",retour);
	
	printf("Image2: \n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d ",image2[i][j]);
		}
		printf("\n");
	}
	printf("Lignes %d colonnes %d\n",lignes2,colonnes2);
	
	
	int couleurPrep;
	
	couleurPrep=pgm_couleur_preponderante(image1,lignes1,colonnes1);
	
	printf("Couleur preponderante: %d\n",couleurPrep);
	
	pgm_creer_negatif(image1,lignes1,colonnes1,val);
	
	printf("Image1 negatif:\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d ",image1[i][j]);
		}
		printf("\n");
	}
	
    //printf("-> Debut!\n");

	//// exemple d'appel de fonction
    //retour = pgm_lire(nom, image1, 
                      //&lignes1, &colonnes1, 
                      //&maxval, &metadonnees);

	//// exemple detraitement d'un code de retour (erreur ou reussite)
	//printf("-> Retour: ");
	//if (retour == OK)
		//printf("-> OK");
	//else
		//printf("-> ERREUR");
	//printf("\n");

	//// autre exemple d'appel de fonction
    //pgm_ecrire(nom, image1, 
               //lignes1, colonnes1, 
               //maxval, metadonnees);

    //printf("-> Fin!\n");

    return 0;
}
