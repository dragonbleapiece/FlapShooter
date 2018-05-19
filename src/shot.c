/*
 * shot.c
 * Déclaration des fonctions des projectiles
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */


#include "shot.h"

void entityShot(Entity E, Level* level, float sizeX, float sizeY, Texture *t, float speedX, float speedY, BoundingBoxList boundingBox) {
  EntityList shot = allocEntity(E.x + E.sizeX * E.shotX, E.y + E.sizeY * E.shotY, sizeX, sizeY, 1, E.attack, t, boundingBox);

  if (shot != NULL) {
    shot->speedX = speedX;
    shot->speedY = speedY;
    addEntityToList(&(level->projectiles), shot);
  } else {
    printf("Cannot shot\n");
  }
}

void playerShot(Level* level) {

  Texture *t = createTextureToList(&(level->textures), SRC_CARROTBALL, 1, 1);
  if (t != NULL)
    entityShot(*(level->player), level, 16. / (float) UNITE, 16. / (float) UNITE, t, LEVEL_SPEED * level->speedCoeff + PROJECTILE_SPEED, 0., createAABBBoundingBox(1, 0.5));
  else printf("Memory run out !\n");
}
