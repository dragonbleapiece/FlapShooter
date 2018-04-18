/*
 * tools.h
 * Déclaration de fonctions utiles
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef TOOLS_H
#define TOOLS_H
#include <string.h>

/*
 * getFileNameExt
 * Retourne l'extension du fichier <fileName>
 */
const char *getFileNameExt(const char *fileName);

/*
 * strIndexOf
 * Retourne le premier indice pour lequel on trouve la chaine <str> 
 * dans le tableau <tab> de taille <size>
 * Retourne -1 si l'élément cherché n'est pas présent dans le tableau
 */
int strIndexOf(const char str[], const char *tab[], int size);

#endif
