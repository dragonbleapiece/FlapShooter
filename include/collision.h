/*
 * collision.h
 * Déclaration de la structure et des fonctions de gestion des collisions
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef COLLISION_H
#define COLLISION_H
#include "settings.h"
#include "bounding.h"
#include "entity.h"

/*
 * File de collision entre entités
 */
typedef struct collision {
  Entity *E;
  struct collision* next; /* Pointeur sur la collision suivante dans la liste */
} Collision, *CollisionList;

/*
 * pushCollision
 * Rajoute une nouvelle collision a la fin de la file
 * Alloue la mémoire et quitte le programme en cas d'erreur d'allocation
 * <*L> : Pointeur sur la liste de collision
 * <*E> : Pointeur sur l'entité
 */
void pushCollision(CollisionList *L, Entity *E);

/*
 * popCollision
 * Supprime la première cellule de la file de colision en libérant la mémoire
 * <*L> : Pointeur sur la liste de collision
 * Retourne l'entité de la liste
 */
Entity* popCollision(CollisionList *L);

/*
 * isColliding
 * Test si l'entité <E1> est en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
 */
int isColliding(Entity E1, Entity E2);

/*
 * isCollidingWith
 * Test si l'entité <E> est en collision avec l'une des entités de la liste <L>
 * <xMax> : Coordonnée maximum en x des entités a tester
 * Retourne une file de collision des entités qui sont en collision avec <E>
 * Retourne NULL si aucune collision
 */
CollisionList isCollidingWith(Entity E, EntityList L, float xMax);

/*
 * willColliding
 * Test si l'entité <E1> entrera en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
 */
int willColliding(Entity E1, Entity E2);

/*
 * willCollidingWith
 * Test si l'entité <E> rentrera en collision avec l'une des entités de la liste <L>
 * <xMax> : Coordonnée maximum en x des entités a tester
 * Retourne une file de collision des entités qui sont en collision avec <E>
 * Retourne NULL si aucune collision
 */
CollisionList willCollidingWith(Entity E, EntityList L, float xMax);

void freeCollisionList(CollisionList collision);

int isCollidingOnce(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

int isCollidingNTimes(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*), int n);

int isCollidingRepeat(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

CollisionList areCollidingOnce(EntityList E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

void removeCollisionListFromEntityList(EntityList *L, CollisionList *collisions);

#endif
