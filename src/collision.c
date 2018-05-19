/*
 * collision.c
 * Déclaration de la structure et des fonctions de gestion des collisions
 *
 * N.B. Les descriptifs des fonctions sont dans collision.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "collision.h"

void pushCollision(CollisionList *L, Entity *E) {
  Collision *newCell = (Collision *) malloc(sizeof (newCell));
  if (!newCell) {
    printf("Memory run out\n");
    exit(1);
  }
  newCell->E = E;
  newCell->next = NULL;
  if (*L == NULL)
    *L = newCell;
  else {
    CollisionList tmp = *L;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = newCell;
  }
}

Entity* popCollision(CollisionList *L) {
  if (L == NULL || *L == NULL) return NULL;
  Collision *firstCell = *L;
  Entity* tmp = firstCell->E;
  *L = (*L)->next;
  free(firstCell);
  return tmp;
}

int isColliding(Entity E1, Entity E2) {
  BoundingBoxList B1 = E1.boundingBox, B2 = E2.boundingBox;
  BoundingShape S1, S2;

  int r = 0;
  while (B1 != NULL && !r) {
    S1 = convertShapeToAbsolute(B1->shape, B1->type, E1.x, E1.y, E1.sizeX, E1.sizeY);
    while (B2 != NULL && !r) {
      S2 = convertShapeToAbsolute(B2->shape, B2->type, E2.x, E2.y, E2.sizeX, E2.sizeY);
      r = isCollidingShape(S1, B1->type, S2, B2->type);
      B2 = B2->next;
    }
    B1 = B1->next;
  }
  return r;
}

CollisionList isCollidingWith(Entity E, EntityList L, float xMax) {
  CollisionList collisions = NULL;
  while (L != NULL && L->x <= xMax) {
    if (L->life != 0 && isColliding(E, *L))
      pushCollision(&collisions, L);
    L = L->next;
  }
  return collisions;
}

int willColliding(Entity E1, Entity E2) {
  BoundingBoxList B1 = E1.boundingBox, B2 = E2.boundingBox;
  BoundingShape S1, S2;

  int r = 0;
  while (B1 != NULL && !r) {
    S1 = convertShapeToAbsolute(B1->shape, B1->type, E1.x + convert_speed(E1.speedX), E1.y + convert_speed(E1.speedY), E1.sizeX, E1.sizeY);
    while (B2 != NULL && !r) {
      S2 = convertShapeToAbsolute(B2->shape, B2->type, E2.x + convert_speed(E2.speedX), E2.y + convert_speed(E2.speedY), E2.sizeX, E2.sizeY);
      r = isCollidingShape(S1, B1->type, S2, B2->type);
      B2 = B2->next;
    }
    B1 = B1->next;
  }
  return r;
}

CollisionList willCollidingWith(Entity E, EntityList L, float xMax) {
  CollisionList collisions = NULL;
  while (L != NULL && L->x <= xMax) {
    if (L->life != 0 && willColliding(E, *L))
      pushCollision(&collisions, L);
    L = L->next;
  }
  return collisions;
}

void freeCollisionList(CollisionList collision) {
  if(collision != NULL) {
    freeCollisionList(collision->next);
    free(collision);
  }
}

int isCollidingNTimes(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*), int n) {
  CollisionList collision;
  Entity *obstacle;
  int k = 0;
  collision = isCollidingWith(*E, L, xMax);
  obstacle = popCollision(&collision);
  while(obstacle != NULL && k < n) {
    callback(E, obstacle);
    obstacle = popCollision(&collision);
    ++k;
  }

  freeCollisionList(collision);

  return k;

}

int isCollidingOnce(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*)) {
  return isCollidingNTimes(E, L, xMax, callback, 1);
}

int isCollidingRepeat(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*)) {
  CollisionList collision;
  Entity *obstacle;
  int k = 0;
  collision = isCollidingWith(*E, L, xMax);
  obstacle = popCollision(&collision);
  while(obstacle != NULL) {
    callback(E, obstacle);
    obstacle = popCollision(&collision);
    ++k;
  }

  return k;

}

CollisionList areCollidingOnce(EntityList E, EntityList L, float xMax, void (*callback)(Entity*, Entity*)) {
  CollisionList collisions = (CollisionList) malloc(sizeof(*collisions));
  while (E != NULL) {
    if(isCollidingOnce(E, L, xMax, callback)) {
      pushCollision(&collisions, E);
    }
    E = E->next;
  }

  return collisions;
}

void removeCollisionListFromEntityList(EntityList *L, CollisionList collisions) {
  EntityList e = popCollision(&collisions);
  while(e != NULL) {
    if(e->life == 0) removeEntityToList(L, e);
    e = popCollision(&collisions);
  }
}
