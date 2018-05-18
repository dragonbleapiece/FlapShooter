/*
 * controls.c
 * Déclaration de la structure et des fonctions de controles
 *
 * N.B. Les descriptifs des fonctions sont dans display.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "controls.h"

Controls initControls() {
  Controls c;
  c.space = 0;
  c.up = 0;
  c.down = 0;
  c.left = 0;
  c.right = 0;

  return c;
}

void executeControls(Controls c, Level level, Camera cam) {

  Entity *player = level.player;
  Entity *obstacle;
  CollisionList obstaclesCollision;

  if (c.space == 1) {

  }

  if (c.up) player->speedY = clamp(player->speedY - ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c.down && player->speedY < 0) player->speedY = clamp(player->speedY + INERTIE, -MAXSPEED, 0);

  if (c.down) player->speedY = clamp(player->speedY + ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c.up && player->speedY > 0) player->speedY = clamp(player->speedY - INERTIE, 0, MAXSPEED);

  if (c.left) player->speedX = clamp(player->speedX - ACCELERATION, -MAXSPEED, MAXSPEED + LEVEL_SPEED);
  else if (!c.right && player->speedX < LEVEL_SPEED) player->speedX = clamp(player->speedX + INERTIE, -MAXSPEED, LEVEL_SPEED);

  if (c.right) player->speedX = clamp(player->speedX + ACCELERATION, -MAXSPEED, MAXSPEED + LEVEL_SPEED);
  else if (!c.left && player->speedX > LEVEL_SPEED) player->speedX = clamp(player->speedX - INERTIE, LEVEL_SPEED, MAXSPEED + LEVEL_SPEED);

  //printf("%f %f \n", player->speedX, player->speedY);
  player->speedX = clamp(player->speedX + player->x, cam.xMin, cam.xMin + (cam.xMax - cam.xMin) * FREE_MOVES - player->sizeX) - player->x;
  player->speedY = clamp(player->speedY + player->y, cam.yMin, cam.yMax - player->sizeY) - player->y;

  obstaclesCollision = willCollidingWith(*player, level.obstacles, cam.xMax);
  obstacle = popCollision(&obstaclesCollision);
  /* À améliorer en rendant dépendant aux bounding box et en le debuguant */
  while (obstacle != NULL) {

    if (!willColliding(*player, *obstacle)) {
      freeCollisionList(obstaclesCollision);
      obstaclesCollision = willCollidingWith(*player, level.obstacles, cam.xMax);
    } else {

      if (player->x + player->sizeX <= obstacle->x) {
        player->speedX = (player->sizeX + player->x - (obstacle->x + player->speedX - obstacle->speedX)) * BOUND;
        player->speedX = clamp_end(player->sizeX + player->x + player->speedX, obstacle->x + obstacle->speedX) - (player->sizeX + player->x);
      }
      else if (player->x >= obstacle->x + obstacle->sizeX) {
        player->speedX = (player->x - (obstacle->x + obstacle->sizeX + player->speedX - obstacle->speedX)) * BOUND;
        player->speedX = clamp_start(player->x + player->speedX, obstacle->x + obstacle->speedX) - (player->x);
      }


      if (player->y + player->sizeY <= obstacle->y) {
        player->speedY = (player->sizeY + player->y - (obstacle->y + player->speedY - obstacle->speedY)) * BOUND;
        player->speedY = clamp_end(player->sizeY + player->y + player->speedY, obstacle->y + obstacle->speedY) - (player->sizeY + player->y);
      } else if (player->y >= obstacle->y + obstacle->sizeY) {
        player->speedY = (player->y - (obstacle->y + obstacle->sizeY + player->speedY - obstacle->speedY)) * BOUND;
        player->speedY = clamp_start(player->y + player->speedY, obstacle->y + obstacle->speedY) - (player->y);
      }


    }



    obstacle = popCollision(&obstaclesCollision);
  }


  translateEntityBySpeed(player);
}
