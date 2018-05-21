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
    removeEntityToList(&level->bonus, obstacle); // On détruit l'obstacle
  }

  /* Effets des bonnus */
  if (haveBonus(&level->currentBonus, SPEED_BONUS)) { // Vitesse
    level->speedCoeff = SPEED_BONUS_COEFF;
  } else {
    level->speedCoeff = 1.;
  }



}
