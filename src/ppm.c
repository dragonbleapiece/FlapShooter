/*
 * ppm.c
 * Déclaration de la structure et des fonctions de gestion de fichier au format PPM
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "ppm.h"

PPMImage *generatePPMImageFromFile(const char filename[]) {


  char buff[3], c;
  PPMImage *img;
  FILE *fp;
  int temp, comp, i = 0, j = 0;
  /*ouvre le fichier PPM en lecture*/
  fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Unable to open file '%s'\n", filename);
    return NULL;
  }

  /*lit le format de l'image*/
  if (!fscanf(fp, " %2s", buff)) {
    perror(filename);
    return NULL;
  }

  /*vérifie le format de l'image*/
  if (buff[0] != 'P' || buff[1] != '2') {
    fprintf(stderr, "Invalid image format (must be 'P2')\n");
    return NULL;
  }


  /*alloue de la mémoire pour l'image*/
  img = (PPMImage *) malloc(sizeof (PPMImage));
  if (!img) {
    fprintf(stderr, "Unable to allocate memory\n");
    return NULL;
  }

  /*vérifie si il y a des commentaires*/

  while (fscanf(fp, " %c", &c) == 1 && c == '#') {
    while (getc(fp) != '\n');
  }

  ungetc(c, fp);
  /*lit la taille de l'image*/
  if (fscanf(fp, " %d %d", &img->x, &img->y) != 2) {
    fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
    return NULL;
  }

  /*lit la profondeur des composants*/
  if (fscanf(fp, " %d", &comp) != 1) {
    fprintf(stderr, "Invalid component (error loading '%s')\n", filename);
    return NULL;
  }

  /*allocation mémoire pour les données des pixels*/
  img->data = allocTable(img->x, img->y);


  i = 0;

  /*lit les données des pixels du fichier*/
  while (j < img->y && fscanf(fp, " %d", &temp) == 1 && temp <= comp) {
    img->data[i][j] = temp;
    ++i;
    if (i >= img->x) {
      ++j;
      i = 0;
    }
  }

  if (j < img->y) {
    fprintf(stderr, "Error loading image '%s'\n", filename);
    return NULL;
  }

  fclose(fp);

  return img;
}

void printPPMImage(PPMImage ppm) {
  int i, j;
  for (j = 0; j < ppm.y; ++j) {
    for (i = 0; i < ppm.x; ++i) {
      printf("%d ", ppm.data[i][j]);
    }
    printf("\n");
  }
}

void freePPMImage(PPMImage *ppm) {
  freeTable(ppm->data);
  free(ppm);
}
