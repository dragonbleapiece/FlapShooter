/*
 * level.c
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

 #include "level.h"
 #include "entity.h"
 #include "ppm.h"

 Level generateLevelFromFile(const char fileName[]) {


   Level level;
   PPMImage *img = generatePPMImageFromFile(filename);

   if(!img) {
     fprintf(stderr, "Cannot start the game...\n");
     exit(1);
   }

   int i, j;

   for(i = 0; i < img->x; ++i) {
     for(j = 0; j < img->y; ++j) {
       if(!addElementToLevel(img->data[i][j], &level, i, j)) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
       }
     }
   }

   free(img);
   return level;
 }

 int addElementToLevel(int code, Level *level) {
   int r = 1;
   switch(code) {
     default:
      break;
   }

   return r;
 }
