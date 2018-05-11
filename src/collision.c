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
  if (*L == NULL) return NULL;
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
    S1 = convertShapeToAbsolute(B1->shape, B1->type, E1.x + E1.speedX, E1.y + E1.speedY, E1.sizeX, E1.sizeY);
    while (B2 != NULL && !r) {
      S2 = convertShapeToAbsolute(B2->shape, B2->type, E2.x + E2.speedX, E2.y + E2.speedY, E2.sizeX, E2.sizeY);
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