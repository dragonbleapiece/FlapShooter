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
 #include "settings.h"

 Level generateLevelFromFile(const char filename[]) {

   Level level;
   initialiseLevel(&level);
   PPMImage *img = generatePPMImageFromFile(filename);

   //printPPMImage(*img);

   if(!img) {
     fprintf(stderr, "Cannot start the game...\n");
     exit(1);
   }

   level.height = img->y;
   level.width = img->x;

   int i, j;

   for(i = 0; i < img->x; ++i) {
     for(j = 0; j < img->y; ++j) {
       if(!addEntityToLevel(img->data[i][j], &level, i, j)) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
       }
     }
   }

   freePPMImage(img);
   return level;
 }

void initialiseLevel(Level *level) {
  level->player = NULL;
  level->obstacles = NULL;
  level->ennemies = NULL;
  level->bonus = NULL;
  level->projectiles = NULL;
}

 int addEntityToLevel(EntityCode code, Level *level, float x, float y) {
   int r = 1;
   Entity *e;
   switch(code) {
      case VOID_CODE:
        break;

      case PLAYER_CODE:
        e = allocEntity(x * UNITE, y * UNITE, 2 * UNITE, 2 * UNITE, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->player, e);
        else r = 0;
        break;

      case ENNEMYONE_CODE:
        e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->ennemies, e);
        else r = 0;
        break;

      case ENNEMYTWO_CODE:
        e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->ennemies, e);
        else r = 0;
        break;

      case OBSTACLE_CODE:
        e = allocEntity(x * UNITE, y * UNITE, UNITE, UNITE, -1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->obstacles, e);
        else r = 0;
        break;

      case DESTRUCTIBLE_CODE:
        e = allocEntity(x * UNITE, y * UNITE, UNITE, UNITE, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->obstacles, e);
        else r = 0;
        break;

      case BONUS_CODE:
        e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->bonus, e);
        else r = 0;
        break;

      case PROJECTILE_CODE:
        e = allocEntity(x * UNITE, y * UNITE, 0.0, 0.0, 1, 1, NULL, NULL);
        if(e != NULL) addEntityToList(&level->projectiles, e);
        else r = 0;
        break;

      default:
        r = 0;
        break;
   }

   return r;
 }

 void freeLevel(Level *level) {
   freeEntityList(&level->player);
   freeEntityList(&level->obstacles);
   freeEntityList(&level->ennemies);
   freeEntityList(&level->bonus);
   freeEntityList(&level->projectiles);
 }
