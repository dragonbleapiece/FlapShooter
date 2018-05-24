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
 * File de collisions entre entités
 */
typedef struct collision {
  Entity *E;
  struct collision* next; /* Pointeur sur la collision suivante dans la liste */
} Collision, *CollisionList;

/*
 * pushCollision
 * Rajoute une nouvelle collision à la fin de la file
 * Alloue la mémoire et quitte le programme en cas d'erreur d'allocation
 * <*L> : Pointeur sur la liste de collisions
 * <*E> : Pointeur sur l'entité
 */
void pushCollision(CollisionList *L, Entity *E);

/*
 * popCollision
 * Supprime la première cellule de la file de colisions en libérant la mémoire
 * <*L> : Pointeur sur la liste de collisions
 * Retourne l'entité de la liste
 */
Entity* popCollision(CollisionList *L);

/*
 * isColliding
 * Teste si l'entité <E1> est en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
 */
int isColliding(Entity E1, Entity E2);

/*
 * isCollidingWith
 * Teste si l'entité <E> est en collision avec l'une des entités de la liste <L>
 * <xMax> : Coordonnée maximum en x des entités à tester
 * Retourne une file de collisions des entités qui sont en collision avec <E>
 * Retourne NULL si aucune collision
 */
CollisionList isCollidingWith(Entity E, EntityList L, float xMax);

/*
 * willColliding
 * Teste si l'entité <E1> entrera en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
 */
int willColliding(Entity E1, Entity E2);

/*
 * willCollidingWith
 * Teste si l'entité <E> rentrera en collision avec l'une des entités de la liste <L>
 * <xMax> : Coordonnée maximum en x des entités à tester
 * Retourne une file de collisions des entités qui sont en collision avec <E>
 * Retourne NULL si aucune collision
 */
CollisionList willCollidingWith(Entity E, EntityList L, float xMax);

/*
 * freeCollisionList
 * Libère l'espace alloué pour la liste de collisions
 * <collision> : liste de collisions
 */
void freeCollisionList(CollisionList collision);

/*
 * isCollidingOnce
 * Vérifie si une collision se fait entre une entité et une liste d'entités
 * S'il y a collision, appelle le callback pour les entités impliquées
 * <*E> : pointeur sur entité
 * <L> : liste d'entités
 * <xMax> : Coordonnée maximum en x des entités à tester
 * <*callback> : fonction de callback(Entity*, Entity *)
 * Renvoie 1 s'il y a eu collision, 0 sinon
 */
int isCollidingOnce(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

/*
 * isCollidingNTimes
 * Vérifie si 0 jusqu'à <n> collisions se font entre une entité et une liste d'entités
 * S'il y a collision, appelle le callback pour les entités impliquées
 * <*E> : pointeur sur entité
 * <L> : liste d'entités
 * <xMax> : Coordonnée maximum en x des entités à tester
 * <*callback> : fonction de callback(Entity*, Entity *)
 * <n> : nombre max de collisions
 * Renvoie le nombre de collisions obtenues
 */
int isCollidingNTimes(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*), int n);

/*
 * isCollidingRepeat
 * Vérifie si une ou plusieurs collisions se font entre une entité et une liste d'entités
 * S'il y a collision, appelle le callback pour les entités impliquées
 * <*E> : pointeur sur entité
 * <L> : liste d'entités
 * <xMax> : Coordonnée maximum en x des entités à tester
 * <*callback> : fonction de callback(Entity*, Entity *)
 * Renvoie le nombre de collisions obtenues
 */
int isCollidingRepeat(Entity *E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

/*
 * areCollidingOnce
 * Vérifie si une collision se fait entre deux listes d'entités
 * S'il y a collision, appelle le callback pour les entités impliquées
 * <E> : liste d'entités
 * <L> : liste d'entités
 * <xMax> : Coordonnée maximum en x des entités à tester
 * <*callback> : fonction de callback(Entity*, Entity *)
 * Renvoie le nombre de collisions obtenues
 */
CollisionList areCollidingOnce(EntityList E, EntityList L, float xMax, void (*callback)(Entity*, Entity*));

/*
 * removeCollisionListFromEntityList
 * Supprime l'entité impliquée dans une collision de la liste d'entités si sa vie est à 0
 * <*L> : pointeur sur la liste d'entités
 * <collisions> : liste de collisions
 */
void removeCollisionListFromEntityList(EntityList *L, CollisionList collisions);

#endif
