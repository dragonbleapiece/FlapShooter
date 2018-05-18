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
  BoundingBox *bbPlayer, *bbObstacle;
  BoundingShape bboxPlayer, bboxObstacle;

  float levelSpeed = LEVEL_SPEED * level.speedCoeff;
  float maxspeed = MAXSPEED + level.speedCoeff;
  float acceleration = ACCELERATION * level.speedCoeff;

  if (c.space == 1) {

  }


  if (c.up) player->speedY = clamp(player->speedY - acceleration, -maxspeed, maxspeed);
  else if (!c.down && player->speedY < 0) player->speedY = clamp(player->speedY + INERTIE, -maxspeed, 0);

  if (c.down) player->speedY = clamp(player->speedY + acceleration, -maxspeed, maxspeed);
  else if (!c.up && player->speedY > 0) player->speedY = clamp(player->speedY - INERTIE, 0, maxspeed);

  if (c.left) player->speedX = clamp(player->speedX - acceleration, -maxspeed, maxspeed + levelSpeed);
  else if (!c.right && player->speedX < levelSpeed) player->speedX = clamp(player->speedX + INERTIE, -maxspeed, levelSpeed);

  if (c.right) player->speedX = clamp(player->speedX + acceleration, -maxspeed, maxspeed + levelSpeed);
  else if (!c.left && player->speedX > levelSpeed) player->speedX = clamp(player->speedX - INERTIE, levelSpeed, maxspeed + levelSpeed);

  //printf("%f %f \n", player->speedX, player->speedY);
  player->speedX = (clamp(convert_speed(player->speedX) + player->x, cam.xMin, cam.xMin + (cam.xMax - cam.xMin) * FREE_MOVES - player->sizeX) - player->x) * 1. / ( floor(ROUND_DECIMAL / FPS) / ROUND_DECIMAL);
  player->speedY = (clamp(convert_speed(player->speedY) + player->y, cam.yMin, cam.yMax - player->sizeY) - player->y) * 1. / ( floor(ROUND_DECIMAL / FPS) / ROUND_DECIMAL);

  obstaclesCollision = willCollidingWith(*player, level.obstacles, cam.xMax);
  obstacle = popCollision(&obstaclesCollision);
  /* À améliorer en rendant dépendant aux bounding box et en le debuguant */
  while (obstacle != NULL) {

    if (!willColliding(*player, *obstacle)) {
      freeCollisionList(obstaclesCollision);
      obstaclesCollision = willCollidingWith(*player, level.obstacles, cam.xMax);
    } else {

      bbPlayer = player->boundingBox;

      while(bbPlayer != NULL) {

        bboxPlayer = convertShapeToAbsolute(bbPlayer->shape, bbPlayer->type, player->x, player->y, player->sizeX, player->sizeY);

        bbObstacle = obstacle->boundingBox;

        while(bbObstacle != NULL) {

          bboxObstacle = convertShapeToAbsolute(bbObstacle->shape, bbObstacle->type, obstacle->x, obstacle->y, obstacle->sizeX, obstacle->sizeY);

          if (bboxPlayer.box.xMax <= bboxObstacle.box.xMin) {
            player->speedX = (bboxPlayer.box.xMax - (bboxObstacle.box.xMin + player->speedX - obstacle->speedX)) * BOUND;
            player->speedX = clamp_end(bboxPlayer.box.xMax + player->speedX, bboxObstacle.box.xMin + obstacle->speedX) - (bboxPlayer.box.xMax);
          }
          else if (bboxPlayer.box.xMin >= bboxObstacle.box.xMax) {
            player->speedX = (bboxPlayer.box.xMin - (bboxObstacle.box.xMax + player->speedX - obstacle->speedX)) * BOUND;
            player->speedX = clamp_start(bboxPlayer.box.xMin + player->speedX, bboxObstacle.box.xMin + obstacle->speedX) - (bboxPlayer.box.xMin);
          }


          if (bboxPlayer.box.yMax <= bboxObstacle.box.yMin) {
            player->speedY = (bboxPlayer.box.yMax - (bboxObstacle.box.yMin + player->speedY - obstacle->speedY)) * BOUND;
            player->speedY = clamp_end(bboxPlayer.box.yMax + player->speedY, bboxObstacle.box.yMin + obstacle->speedY) - (bboxPlayer.box.yMax);
          }
          else if (bboxPlayer.box.yMin >= bboxObstacle.box.yMax) {
            player->speedY = (bboxPlayer.box.yMin - (bboxObstacle.box.yMax + player->speedY - obstacle->speedY)) * BOUND;
            player->speedY = clamp_start(bboxPlayer.box.yMin + player->speedY, bboxObstacle.box.yMin + obstacle->speedY) - (bboxPlayer.box.yMin);
          }

          bbObstacle = bbObstacle->next;

        }

        bbPlayer = bbPlayer->next;

      }

    }



    obstacle = popCollision(&obstaclesCollision);
  }


  translateEntityBySpeed(player);
}
