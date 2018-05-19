#include "events.h"

void eventsInLevel(Level *level, Camera cam) {
  CollisionList toDestroyed;
  toDestroyed = areCollidingOnce(level->projectiles, level->obstacles, cam.xMax, attacksBetween);
  removeCollisionListFromEntityList(&(level->projectiles), toDestroyed);


}
