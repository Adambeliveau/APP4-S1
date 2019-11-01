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
	int nb_pointVirgule = 0;
	
	fPointer = fopen(nom_fichier, "r");
	
	if(!fPointer)
	{
		fclose(fPointer);
		return ERREUR_FICHIER;
	}
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	fgets(Deuxieme_ligne, MAX_CHAINE, fPointer);
	
	longueur = strlen(Premiere_ligne);
	if((Deuxieme_ligne[0] == 'P' && Deuxieme_ligne[1] != '2') ||(Premiere_ligne[0] == 'P' && Premiere_ligne[1] != '2') || (Premiere_ligne[0] != 'P' && Deuxieme_ligne[0] != 'P') || (Premiere_ligne[0] == 'P' && Deuxieme_ligne[0] == 'P'))
	{
		fclose(fPointer);
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
					nb_pointVirgule++;
					j = i;
				}
				else
				{
					fclose(fPointer);
					return ERREUR_FORMAT;
				}
			}
			if (nb_pointVirgule != 2)
			{
				fclose(fPointer);
				return ERREUR_FORMAT;
			}
		}
		
		
		if(IsMeta == 0)
		{
			fseek(fPointer, 0, SEEK_SET);
			fgets(temporaire, MAX_CHAINE, fPointer);
		}
		fscanf(fPointer, "%d", p_lignes);
		
		if(*p_lignes > MAX_LARGEUR || *p_lignes < 0 )
		{
			fclose(fPointer);
			return ERREUR_TAILLE;
		} 
		 
		fscanf(fPointer, "%d", p_colonnes);
		
		if(*p_colonnes > MAX_HAUTEUR || *p_colonnes < 0)
		{
			fclose(fPointer);
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
		fclose(fPointer);
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
		fprintf(fPointer,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
	}
	fprintf(fPointer,"P2\n");
	fprintf(fPointer,"%d %d\n",colonnes,lignes);
	fprintf(fPointer,"%d\n",maxval);
	for (int i = 0; i < lignes ; i++)
	{
		for(int j = 0 ; j < colonnes ; j++)
		{
			fprintf(fPointer, "%d ",matrice[i][j]);
			if(matrice[i][j] == 115)
			{
				fprintf(fPointer,"\n");
			}
		}
	}
	fclose(fPointer);
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
	if (pgm_sont_identiques(matrice1,lignes1,colonnes1,matrice2,*p_lignes2,*p_colonnes2)==OK)
		return OK;
	else
		return ERREUR;
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
	int nbLignes=(lignes2-lignes1)+1;
	int nbColonnes=(colonnes2-colonnes1)+1;
	int iLigne=0;
	int jColonne=0;
	
	*p_lignes=nbLignes;
	*p_colonnes=nbColonnes;
	
	if(nbLignes<0||nbColonnes<0||lignes1<1||lignes2<1||colonnes1<1||colonnes2<1||lignes2>*p_lignes||lignes1>*p_lignes||colonnes1>*p_colonnes||colonnes2>*p_colonnes)
	{
		verif=ERREUR;
	}
	
	else{
		int matriceExt[nbLignes][nbColonnes];
		*p_lignes=nbLignes;
		*p_colonnes=nbColonnes;
		//extraction de la matrice
		for(int i=lignes1;i<=lignes2;i++)
		{
			for(int j=colonnes1;j<=colonnes2;j++)
			{
				matriceExt[iLigne][jColonne]=matrice[i][j];
				jColonne++;	
			}
			jColonne=0;
			iLigne++;
		}
		//superposition de la matrice extraite au coin superieur gauche
		for(int i=0;i<nbLignes;i++)
		{
			for(int j=0;j<nbColonnes;j++){
				matrice[i][j]=matriceExt[i][j];
			}
		}
	}
	return verif;

}
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	if (valeur > maxval || maxval < 0 || lignes < 0 || colonnes < 0)
	{
		return ERREUR;
	}
	for (int i = 0; i < lignes; i++)
	{
		for(int j = 0 ; j < colonnes ; j++)
		{
			matrice[i][j] += valeur;
			if(matrice[i][j] > maxval)
			{
				matrice[i][j] = maxval;
			}
			if(matrice[i][j] < 0)
			{ 
				matrice[i][j] = 0;
			}
		}
	}
	return OK;
}
int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	int temporaire[MAX_HAUTEUR][MAX_LARGEUR];
	
	if(*p_lignes <= 0 || *p_colonnes <= 0 || *p_lignes > MAX_HAUTEUR || *p_colonnes > MAX_LARGEUR)
	{
		return ERREUR;
	}

	if(sens == 1)
	{
		for(int i=0; i<*p_colonnes; i++)
		{
			for (int j=0; j<*p_lignes; j++)
			{
				temporaire[i][j]=matrice[(*p_lignes-1)-j][i];
			}

		}
		
		for (int i=0;i<*p_colonnes;i++)
			{ 
				for (int j=0; j<*p_lignes;j++)
				{
					matrice[i][j] = temporaire[i][j];
				}
			}
	}
	else if(sens == 0)
	{
		for(int i=0; i<*p_lignes; i++)
		{
			for (int j=0; j<*p_colonnes; j++)
			{
				temporaire[(*p_colonnes-1)-j][i]=matrice[i][j];
			}

		}
		
		for (int i=0;i<*p_colonnes;i++)
			{ 
			for (int j=0; j<*p_lignes;j++)
				{
					matrice[i][j] = temporaire[i][j];
				}
			}
		
	}
	else
	{
		return ERREUR;
	}
	
	
	int temp=*p_lignes;
	*p_lignes=*p_colonnes;
	*p_colonnes=temp;
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
	{;
		return ERREUR_FICHIER;
	}
	
	fgets(Premiere_ligne, MAX_CHAINE, fPointer);
	fgets(Deuxieme_ligne, MAX_CHAINE, fPointer);
	
	longueur = strlen(Premiere_ligne);
	if((Deuxieme_ligne[0] == 'P' && Deuxieme_ligne[1] != '3') ||(Premiere_ligne[0] == 'P' && Premiere_ligne[1] != '3') || (Premiere_ligne[0] != 'P' && Deuxieme_ligne[0] != 'P') || (Premiere_ligne[0] == 'P' && Deuxieme_ligne[0] == 'P'))
	{
		return ERREUR_FORMAT;
	}
	
	if(Premiere_ligne[0] == '#' || (Premiere_ligne[0] == 'P' && Premiere_ligne[1] == '3'))
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

		if(*p_lignes == MAX_LARGEUR || *p_lignes < 0)
		{
			return ERREUR_TAILLE;
		} 
		 
		fscanf(fPointer, "%d", p_colonnes);
		
		if(*p_colonnes > MAX_HAUTEUR || *p_colonnes < 0)
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
	if(cpt_pixel-1 != Nb_Pixel)
	{
		return ERREUR_FORMAT;
	}
	fclose(fPointer);
    return OK;
}
int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	printf("nom du fichier : %s\t",nom_fichier);
	FILE * fPointer;
	
	if(lignes == MAX_LARGEUR || lignes < 0)
	{
		printf("1\n");
		return ERREUR;
	} 
	 
	if(colonnes > MAX_HAUTEUR || colonnes < 0)
	{
		printf("1\n");
		return ERREUR;
	}
	fPointer = fopen(nom_fichier, "w");
	
	if (!fPointer)
	{
		return ERREUR;
	}
	
	if(metadonnees.auteur[0] != '\0' || metadonnees.dateCreation[0] != '\0' || metadonnees.lieuCreation[0] != '\0')
	{
		fprintf(fPointer,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
	}
	fprintf(fPointer,"P3\n");
	fprintf(fPointer, "%d", colonnes);
	fprintf(fPointer," %d\n",lignes);
	fprintf(fPointer,"%d\n",maxval);
	for (int i = 0; i < lignes; i++)
	{
		for(int j = 0 ; j < colonnes ; j++)
		{
			fprintf(fPointer, "%d ",matrice[i][j].valeurR);
			fprintf(fPointer, "%d ",matrice[i][j].valeurG);
			fprintf(fPointer, "%d ",matrice[i][j].valeurB);
		}
		fprintf(fPointer, "\n");
	}
	
	fclose(fPointer);
    return OK;
}
int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	struct RGB matrice_temp[MAX_HAUTEUR][MAX_LARGEUR];
	
	if(sens == 1)
	{
		for(int i=0; i<*p_colonnes; i++)
		{
			for (int j=0; j<*p_lignes; j++)
			{
				matrice_temp[i][j].valeurR=matrice[(*p_lignes-1)-j][i].valeurR;
				matrice_temp[i][j].valeurG=matrice[(*p_lignes-1)-j][i].valeurG;
				matrice_temp[i][j].valeurB=matrice[(*p_lignes-1)-j][i].valeurB;
			}

		}
		
		for (int i=0;i<*p_colonnes;i++)
			{ 
				for (int j=0; j<*p_lignes;j++)
				{
					matrice[i][j].valeurR = matrice_temp[i][j].valeurR;
					matrice[i][j].valeurG = matrice_temp[i][j].valeurG;
					matrice[i][j].valeurB = matrice_temp[i][j].valeurB;
				}
			}
		
	}
	else if(sens == 0)
	{
		for(int i=0; i<*p_lignes; i++)
		{
			for (int j=0; j<*p_colonnes; j++)
			{
				matrice_temp[(*p_colonnes-1)-j][i].valeurR=matrice[i][j].valeurR;
				matrice_temp[(*p_colonnes-1)-j][i].valeurG=matrice[i][j].valeurG;
				matrice_temp[(*p_colonnes-1)-j][i].valeurB=matrice[i][j].valeurB;
			}

		}
		
		for (int i=0;i<*p_colonnes;i++)
			{ 
			for (int j=0; j<*p_lignes;j++)
				{
					matrice[i][j].valeurR = matrice_temp[i][j].valeurR;
					matrice[i][j].valeurG = matrice_temp[i][j].valeurG;
					matrice[i][j].valeurB = matrice_temp[i][j].valeurB;
				}
			}
	}
	else
	{
		return ERREUR;
	}
	
	int temp=*p_lignes;
	*p_lignes=*p_colonnes;
	*p_colonnes=temp;

	return OK;
}
int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	//copie des informations
	*p_lignes2=lignes1;
	*p_colonnes2=colonnes1;
	
	//copie de la matrice
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1; j++)
		{
			matrice2[i][j].valeurR=matrice1[i][j].valeurR;
			matrice2[i][j].valeurG=matrice1[i][j].valeurG;
			matrice2[i][j].valeurB=matrice1[i][j].valeurB;
		}
	}
	//Verification 
	//if (pgm_sont_identiques(matrice1,lignes1,colonnes1,matrice2,*p_lignes2,*p_colonnes2)==OK)
		return OK;
	//else
		//return ERREUR;
}
int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int verif=OK;
	//int val1,val2;
	if(lignes1!=lignes2||colonnes1!=colonnes2||lignes1>MAX_HAUTEUR||lignes2>MAX_HAUTEUR||colonnes1>MAX_LARGEUR||colonnes2>MAX_LARGEUR)
		verif=ERREUR;
	else
	{
		for(int i=0;i<lignes1;i++){
			if(verif==OK){
				for(int j=0;j<colonnes1;j++){
					//val1=matrice1[i][j];
					//val2=matrice2[i][j];
					if(matrice1[i][j].valeurR!=matrice2[i][j].valeurR||matrice1[i][j].valeurG!=matrice2[i][j].valeurG||matrice1[i][j].valeurB!=matrice2[i][j].valeurB){
						verif=1;
						break;
					}
				}
			}
		}
	}
	return verif;
}
int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	int verif=OK;
	//int val1,val2;
	if(lignes1!=lignes2||colonnes1!=colonnes2||lignes1>MAX_HAUTEUR||lignes2>MAX_HAUTEUR||colonnes1>MAX_LARGEUR||colonnes2>MAX_LARGEUR)
		verif=ERREUR;
	else
	{
		for(int i=0;i<lignes1;i++){
			if(verif==OK){
				for(int j=0;j<colonnes1;j++){
					//val1=matrice1[i][j];
					//val2=matrice2[i][j];
					if(matrice1[i][j]!=matrice2[i][j]){
						verif=1;
						break;
					}
				}
			}
		}
		
	
	}
	return verif;
}




