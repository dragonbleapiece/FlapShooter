#include "events.h"

void eventsInLevel(Level *level, Camera cam) {
  CollisionList collisions;
  Entity *obstacle;

  /* Collisions missiles-obstacles */
  collisions = areCollidingOnce(level->projectiles, level->obstacles, cam.xMax, attacksBetween);
  freeCollisionList(collisions);

  /* Collisions joueur-bonus */
  collisions = isCollidingWith(*(level->player), level->bonus, cam.xMax);
  while ((obstacle = popCollision(&collisions)) != NULL) {
    createBonusToList(&level->currentBonus, obstacle->entityCode);
    getDamaged(obstacle, -1); // On détruit l'obstacle
  }

  /* Effets des bonnus de VITESSE */
  if (haveBonus(&level->currentBonus, SPEED_BONUS)) {
    level->speedCoeff = SPEED_BONUS_COEFF;
  } else {
    level->speedCoeff = 1.;
  }

  /* Effets des bonnus de TIR */
  if (haveBonus(&level->currentBonus, SHOT_BONUS)) {
    level->player->shotFrequency = PLAYER_SHOT_FREQUENCY / SHOT_BONUS_COEFF;
  } else {
    level->player->shotFrequency = PLAYER_SHOT_FREQUENCY;
  }



}
