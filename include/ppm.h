/*
 * ppm.h
 * Déclaration de la structure et des fonctions de gestion des niveaux
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef PPM_H
#define PPM_H
#include <stdlib.h>
#include <stdio.h>

typedef struct ppmimage {
  int x, y;
  int *data;
} PPMImage;

/*
 * generatePPMImageFromFile
 * Génére une PPMImage depuis un fichier PPM
 * <fileName[]> : nom du fichier au format PPM décrivant le niveau
 * Retourne NULL si l'allocation a échoué, pointeur sur
 */
PPMImage *generatePPMImageFromFile(const char fileName[]);

#endif
