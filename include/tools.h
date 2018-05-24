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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "settings.h"


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

/*
 * clamp
 * Restreint la valeur n dans l'intervalle [a, b] donné
 * <n> : valeur à controler
 * <a> : valeur minimale
 * <b> : valeur maximale
 * Retourne n si n >= a et n <= b, retourne l'extrémité de l'intervalle sinon
 */
float clamp(float n, float a, float b);

/*
 * clamp_start
 * Restreint la valeur n dans l'intervalle [a, .[ donné
 * <n> : valeur à controler
 * <a> : valeur minimale
 * Retourne n si n >= a, retourne a sinon
 */
float clamp_start(float n, float a);

/*
 * clamp_end
 * Restreint la valeur n dans l'intervalle ]., a] donné
 * <n> : valeur à controler
 * <a> : valeur maximale
 * Retourne n si n <= a, retourne a sinon
 */
float clamp_end(float n, float a);

/*
 * swap_a_b
 * intervertit les valeurs de a et de b
 * <*a> : pointeur vers flottant
 * <*b> : pointeur vers flottant
 */
void swap_a_b(float *a, float *b);

/*
 * convert_speed
 * Convertit une vitesse de blocs par seconde en blocs par frame
 */
float convert_speed(float speed);

/*
 * allocTable
 * Alloue un tableau a 2 dimensions dans l'espace mémoire
 * Quitte le programme en cas d'erreur d'allocation
 */
int **allocTable(int lines, int columns);

/*
 * freeTable
 * Libère les données d'un tableau à 2 dimensions
 */
void freeTable(int **table);

/*
 * rand_a_b
 * Retourne un nombre aléatoire entre <a> (inclus) et <b> (exclu)
 * On suppose que a < b
 * N.B. N'initialise pas le rand (seed)
 */
int rand_a_b(int a, int b);

#endif
