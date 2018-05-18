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
#include "settings.h"
#include <math.h>

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
 * Restreint la valeur n dans l'intervalle [a, b] donnée
 * <n> : valeur à controler
 * <a> : valeur minimale
 * <b> : valeur maximale
 * Retourne n si n >= a et n <= b, retourne l'extrémité de l'intervalle sinon
 */
float clamp(float n, float a, float b);

/*
 * clamp_start
 * Restreint la valeur n dans l'intervalle [a, .[ donnée
 * <n> : valeur à controler
 * <a> : valeur minimale
 * Retourne n si n >= a, retourne a sinon
 */
float clamp_start(float n, float a);

/*
 * clamp_end
 * Restreint la valeur n dans l'intervalle ]., a] donnée
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

float convert_speed(float speed);

#endif
