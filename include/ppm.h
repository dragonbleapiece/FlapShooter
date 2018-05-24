/*
 * ppm.h
 * Déclaration de la structure et des fonctions de gestion de fichier au format PPM
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef PPM_H
#define PPM_H
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

typedef struct ppmimage {
  int x, y;
  int **data;
} PPMImage;

/*
 * generatePPMImageFromFile
 * Génère une PPMImage depuis un fichier PPM
 * <fileName[]> : nom du fichier au format PPM décrivant le niveau
 * Retourne NULL si l'allocation a échoué, pointeur sur PPMImage sinon
 */
PPMImage *generatePPMImageFromFile(const char filename[]);

/*
 * printPPMImage
 * Affiche le contenu de <ppm> dans la console 
 */
void printPPMImage(PPMImage ppm);

/*
 * freeLevel
 * Libére la mémoire occupée
 * <*ppm> : Pointeur de la liste triée d'entités
 */
void freePPMImage(PPMImage *ppm);

#endif
