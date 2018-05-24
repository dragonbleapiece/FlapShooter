#include "events.h"

void eventsInLevel(Level *level, Camera cam) {
  CollisionList collisions;
  Entity *obstacle;

  /* Collisions missiles-obstacles */
  collisions = areCollidingOnce(level->projectiles, level->obstacles, cam.xMax, attacksBetween);
  freeCollisionList(collisions);

  /* Collisions missiles-ennemis */
  collisions = areCollidingOnce(level->projectiles, level->ennemies, cam.xMax, attacksBetween);
  freeCollisionList(collisions);

  /* Collisions ennemis-joueur */
  collisions = areCollidingOnce(level->ennemies, level->player, cam.xMax, attacks);
  freeCollisionList(collisions);

  /* Collisions joueur-missiles */
  collisions = areCollidingOnce(level->player, level->projectiles, cam.xMax, attacksBetween);
  freeCollisionList(collisions);

  /* Collisions joueur-bonus */
  collisions = isCollidingWith(*(level->player), level->bonus, cam.xMax);
  while ((obstacle = popCollision(&collisions)) != NULL) {
    if (obstacle->entityCode == LIFE_BONUS)
      getHealed(level->player, 1);
    else
      createBonusToList(&level->currentBonus, obstacle->entityCode);
    getDamaged(obstacle, -1); // On détruit l'obstacle
  }

  /* Effets des bonnus de VITESSE */
  if (haveBonus(&level->currentBonus, SPEED_BONUS))
    level->speedCoeff = SPEED_BONUS_COEFF;
  else
    level->speedCoeff = 1.;


  /* Effets des bonnus de TIR */
  if (haveBonus(&level->currentBonus, SHOT_BONUS))
    level->player->shotFrequency = PLAYER_SHOT_FREQUENCY / SHOT_BONUS_COEFF;
  else
    level->player->shotFrequency = PLAYER_SHOT_FREQUENCY;

  /* Tir des ennemis */
  ennemiesShot(level, cam.xMax);


}
