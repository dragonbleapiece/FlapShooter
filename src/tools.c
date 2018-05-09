/*
 * tools.c
 * Déclaration de fonctions utiles
 *
 * N.B. Les descriptifs des fonctions sont dans tools.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "tools.h"

const char *getFileNameExt(const char *fileName) {
  const char *dot = strrchr(fileName, '.');
  if (!dot || dot == fileName) return "";
  return dot + 1;
}

int strIndexOf(const char str[], const char *tab[], int size) {
  for (int i = 0; i < size; i++)
    if (strcmp(str, tab[i]) == 0)
      return i;
  return -1;
}

float clamp(float n, float a, float b) {
  if(a > b) {
    swap_a_b(&a, &b);
  }
  return clamp_end(clamp_start(n, a), b);
}

float clamp_start(float n, float a) {
  return (n < a) ? a : n;
}

float clamp_end(float n, float a) {
  return (n > a) ? a : n;
}

void swap_a_b(float *a, float *b) {
  float temp = *b;
  *b = *a;
  *a = temp;
}
