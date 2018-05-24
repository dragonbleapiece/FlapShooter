/*
 * shot.c
 * Déclaration des fonctions des projectiles
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */


#include "shot.h"

void entityShot(Entity E, Level* level, float sizeX, float sizeY, Texture *t, float speedX, float speedY, BoundingBoxList boundingBox) {
  EntityList shot = allocEntity(E.x + E.sizeX * E.shotX, E.y + E.sizeY * E.shotY, sizeX, sizeY, 1, E.attack, t, boundingBox, PROJECTILE_CODE);
  if (shot != NULL) {
    shot->speedX = speedX;
    shot->speedY = speedY;
    addEntityToList(&(level->projectiles), shot);
  } else {
    printf("Cannot shot\n");
  }
}

void playerShot(Level* level) {

  setSpriteEntity(level->player, 0, 1);
  Texture *t = createTextureToList(&(level->textures), SRC_CARROTBALL, 2, 7);
  if (t != NULL)
    entityShot(*(level->player), level, 16. / (float) UNITE, 16. / (float) UNITE, t, LEVEL_SPEED * level->speedCoeff + PROJECTILE_SPEED, 0., createAABBBoundingBox(1, 0.5));
  else printf("Memory run out !\n");
}

void ennemyOneShot(Level *level, Entity *ennemy) {

  Texture *t = createTextureToList(&(level->textures), SRC_PIP, 1, 1);
  if (t != NULL)
    entityShot(*ennemy, level, 16. / (float) UNITE, 16. / (float) UNITE, t, -PROJECTILE_SPEED, 0., createAABBBoundingBox(0.25, 0.25));
  else printf("Memory run out !\n");
  ennemy->lastShot = SDL_GetTicks();
}

void ennemiesShot(Level *level, float xMax) {
  EntityList ennemies = level->ennemies;
  while(ennemies != NULL && ennemies->x < xMax) {
    if(ennemies->yTextureIndice == 1 && ennemies->xTextureIndice == 15)
      setSpriteEntity(ennemies, 0, 2);

    if(ennemies->yTextureIndice == 0 && ennemies->lastShot + ENNEMY_SPAWN_SHOT * 1000 < SDL_GetTicks()) {
      setSpriteEntity(ennemies, 0, 1);
    }

    if(ennemies->yTextureIndice == 2 && ennemies->lastShot + ennemies->shotFrequency * 1000 < SDL_GetTicks()) {
      ennemyOneShot(level, ennemies);
    }
    ennemies = ennemies->next;
  }
}
