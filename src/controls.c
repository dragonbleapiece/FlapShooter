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
#include "entity.h"
#include "settings.h"
#include "tools.h"

Controls initControls() {
  Controls c;
  c.space = 0;
  c.up = 0;
  c.down = 0;
  c.left = 0;
  c.right = 0;

  return c;
}

void executeControls(Controls *c, Entity *player) {
  if(c->space == 1) {

  }

  if(c->up) player->speedY = clamp(player->speedY - ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c->down && player->speedY < 0) player->speedY = clamp(player->speedY + INERTIE, -MAXSPEED, 0);

  if(c->down) player->speedY = clamp(player->speedY + ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c->up && player->speedY > 0) player->speedY = clamp(player->speedY - INERTIE, 0, MAXSPEED);

  if(c->left) player->speedX = clamp(player->speedX - ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c->right && player->speedX < 0) player->speedX = clamp(player->speedX + INERTIE, -MAXSPEED, 0);

  if(c->right) player->speedX = clamp(player->speedX + ACCELERATION, -MAXSPEED, MAXSPEED);
  else if (!c->left && player->speedX > 0) player->speedX = clamp(player->speedX - INERTIE, 0, MAXSPEED);

  //printf("%f %f \n", player->speedX, player->speedY);

  translateEntity(player, player->speedX, player->speedY);
}
