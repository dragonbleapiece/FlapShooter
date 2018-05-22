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
  if (a > b) {
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

float convert_speed(float speed) {
  return speed * floor(ROUND_DECIMAL / FPS) / ROUND_DECIMAL;
}

int **allocTable(int lines, int columns) {
  int **table = (int **) malloc(sizeof (int*)*lines);
  int *table2 = (int *) malloc(sizeof (int)*columns * lines);
  if (!table || !table2) {
    fprintf(stderr, "Unable to allocate memory\n");
    return NULL;
  }
  for (int i = 0; i < lines; i++) {
    table[i] = &table2[i * columns];
  }
  return table;
}

void freeTable(int **table) {
  free(table[0]);
  free(table);
}

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}