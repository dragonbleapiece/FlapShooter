/*
 * entity.h
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <GL/gl.h>
#include "bounding.h"

typedef struct entity {
  float x, y; /* Coordonnées de position en bas a gauche de l'entité */
  float sizeX, sizeY; /* Hauteur et largeur de l'entité */
  GLuint textureID;
  int life; /* Vie actuelle de l'entité, -1 si invinsible */
  int maxLife; /* Vie maximal de l'entité (???) */
  int attack; /* Point d'attaque de l'entité */
  BoundingBoxList boundingBox; /* Pointeur sur la liste de bounding box de l'entité */
  struct entity* next; /* Pointeur sur l'entité suivante dans la liste */
} Entity, *EntityList;

/*
 * allocEntity
 * Alloue une entité dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <x> : Position x de l'entité
 * <y> : Position y de l'entité
 * <sizeX> : Largeur de l'entité
 * <sizeY> : Hauteur de l'entité
 * <maxLife> : Vie maximal et actuelle de l'entité
 * <attack> : Point d'attaque de l'entité
 * <textureID> : id de la texture
 * <*boundingBox> : Pointeur sur la/les bounding box de l'entité
 * Retourne un pointeur sur l'entité
 */
Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, GLuint textureID, BoundingBoxList boundingBox);

/*
 * addEntityToList
 * Ajoute l'entité <*E> à la liste <*L> triée par position x
 * <*L> : Pointeur de la liste triée d'entité
 * <*E> : Entité a ajouter, supposé dans aucune liste
 */
void addEntityToList(EntityList *L, Entity *E);

/*
 * printEntityList
 * Affiche récursivement la liste d'entité pour debugage
 * <L> : Pointeur de la liste triée d'entité
 */
void printEntityList(EntityList L);

/*
 * removeEntityToList
 * Enleve l'entité <E> de la liste <*L> et libére la mémoire occupée
 * <*L> : Pointeur de la liste triée d'entité
 * <E> : Entité a supprimer, supposé dans la liste
 * retourne 1 si l'entité a été enlevée, 0 sinon
 */
int removeEntityToList(EntityList *L, EntityList E);

/*
 * freeEntityList
 * Libére la mémoire occupée par toutes les entités de la liste <*L>
 * <*L> : Pointeur de la liste triée d'entité
 */
void freeEntityList(EntityList *L);

/*
 * isColliding
 * Test si l'entité <E1> et en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
 */
int isColliding(Entity E1, Entity E2);

/*
 * isCollidingWith
 * Test si l'entité <E> et en collision avec l'une des entités de la liste <L>
 * <maxX> : Coordonnée maximum en x des entités a tester
 * Retourne un pointeur sur la première entité qui est en collision, NULL sinon
 */
Entity* isCollidingWith(Entity E, EntityList L, float maxX);



#endif
