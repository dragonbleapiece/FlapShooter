/*
 * entity.h
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef ENTITY_H
#define ENTITY_H
#include <math.h>
#include "settings.h"
#include "bounding.h"
#include "texture.h"
#include "route.h"
#include <SDL/SDL.h>

typedef enum entityCode {
  VOID_CODE,
  PLAYER_CODE,
  ENNEMYONE_CODE,
  ENNEMYTWO_CODE,
  OBSTACLE_CODE,
  DESTRUCTIBLE_CODE,
  PROJECTILE_CODE,
  SPEED_BONUS,
  SHOT_BONUS,
  LIFE_BONUS,
  END_CODE
} EntityCode;

typedef struct entity {
  float x, y; /* Coordonnées de position en bas a gauche de l'entité */
  float sizeX, sizeY; /* Hauteur et largeur de l'entité */
  Texture *texture;
  float speedX;
  float speedY;
  float shotX;
  float shotY;
  Uint32 lastShot;
  float shotFrequency;
  int xTextureIndice; /* Division horizontal actuel de l'image pour les sprites, 0 par défaut (1er sprite) */
  int yTextureIndice; /* Division vertical actuel de l'image pour les "sprites",  0 par défaut (1er sprite) */
  int life; /* Vie actuelle de l'entité, -1 si invincible */
  int maxLife; /* Vie maximal de l'entité (???) */
  int attack; /* Point d'attaque de l'entité */
  EntityCode entityCode;
  RouteList routes;
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
 * <entityCode> : code de l'entité
 * Retourne un pointeur sur l'entité
 */
Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, Texture *texture, BoundingBoxList boundingBox, EntityCode entityCode);

/*
 * addEntityToList
 * Ajoute l'entité <*E> à la liste <*L> triée par position x
 * <*L> : Pointeur de la liste triée d'entité
 * <*E> : Entité a ajouter, supposé dans aucune liste
 */
void addEntityToList(EntityList *L, Entity *E);

/*
 * addEntityToUnsortedList
 * Ajoute l'entité <*E> à la liste <*L> sans trie, a la suite
 * <*L> : Pointeur de la liste d'entité
 * <*E> : Entité a ajouter, supposé dans aucune liste
 */
void addEntityToUnsortedList(EntityList *L, Entity *E);

/*
 * printEntityList
 * Affiche récursivement la liste d'entité pour debugage
 * <L> : Pointeur de la liste triée d'entité
 */
void printEntityList(EntityList L);

/*
 * removeEntityToList
 * Enleve l'entité <E> de la liste <*L> et libére la mémoire occupée
 * par l'entité et ses Bounding Box
 * <*L> : Pointeur de la liste triée d'entité
 * <E> : Entité a supprimer, supposé dans la liste
 * retourne 1 si l'entité a été enlevée, 0 sinon
 */
int removeEntityToList(EntityList *L, EntityList E);

/*
 * removeEntityBehind
 * Enleve toutes les entités de la liste <*L> jusqu'à xMax
 * et libére la mémoire occupée. Prend en compte la taille des entités.
 * <*L> : Pointeur de la liste triée d'entité
 * <xMax> : Coordonnée maximum en x des entités a supprimer
 */
void removeEntityBehind(EntityList *L, float xMax);

/*
 * removeEntityInFront
 * Enleve toutes les entités de la liste <*L> après xMax
 * et libére la mémoire occupée. Prend en compte la taille des entités.
 * <*L> : Pointeur de la liste triée d'entité
 * <xMax> : Coordonnée minimum en x des entités a supprimer
 */
void removeEntityInFront(EntityList *L, float xMax);

/*
 * freeEntity
 * Libére la mémoire occupée par l'entité <*E>
 * <*E> : Pointeur de l'entité
 */
void freeEntity(Entity *E);

/*
 * freeEntityList
 * Libére la mémoire occupée par toutes les entités de la liste <*L>
 * <*L> : Pointeur de la liste triée d'entité
 */
void freeEntityList(EntityList *L);

/*
 * isTextured
 * Retourne 1 si l'entité <E> a une texture, 0 sinon
 */
int isTextured(Entity E);

/*
 * upXSpriteEntity
 * Passe a la sprite horizontale suivante pour l'entité <*E>
 * Si on est à la fin de la ligne, le sprite revient a l'état de repos (0,0)
 * <*E> : Entité a modifier
 * Retourne 1 si on est revenu a l'êtat de repos, 0 sinon
 */
int upXSpriteEntity(Entity *E);

/*
 * setSpriteEntity
 * Redéfinis la sprite actuelle de l'entité
 * <*E> : Entité a modifier
 * <x> : Nouvelle division horizontale de l'image pour les sprites, 0 = 1ere sprite
 * <y> : Nouvelle division verticale de l'image pour les sprites, 0 = 1ere sprite
 * Retourne 0 si la nouvelle sprite n'existe pas, 1 sinon
 */
int setSpriteEntity(Entity *E, int x, int y);

/*
 * translateEntity
 * Déplace l'entité <*E> de <x> et <y> unité
 * <*E> : Entité a déplacer
 * <x> : Déplacement en x de l'entité
 * <y> : Déplacement en y de l'entité
 */
void translateEntity(Entity *E, float x, float y);

/*
 * translateEntityList
 * Déplace toutes les entités de la liste <L> de <x> et <y> unité
 * <L> : La liste d'entité a déplacer
 * <x> : Déplacement en x de l'entité
 * <y> : Déplacement en y de l'entité
 * <xMax> : Coordonnée maximum en x des entités a déplacer
 */
void translateEntityList(EntityList L, float x, float y, float xMax);

/*
 * translateEntityBySpeed
 * Déplace l'entité <*E> par son vecteur vitesse
 * N.B. les entités dont la vie est a 0 ne sont pas déplacé
 * <*E> : Entité a déplacer
 */
void translateEntityBySpeed(Entity *E);

/*
 * translateEntityListBySpeed
 * Déplace toutes les entités de la liste <L> par leurs vecteur vitesse
 * <L> : La liste d'entité a déplacer
 * <xMax> : Coordonnée maximum en x des entités a déplacer
 */
void translateEntityListBySpeed(EntityList L, float xMax);

/*
 * attacks
 * Attaque d'une entité sur une autre
 * <*E1> : entité qui attaque
 * <*E2> : entité qui subit
 */
void attacks(Entity *E1, Entity *E2);

/*
 * attacksBetween
 * Attaque réciproque d'une entité sur une autre
 * <E1> : entité impliquée
 * <*E2> : entité impliquée
 */
void attacksBetween(Entity *E1, Entity *E2);

/*
 * getDamaged
 * L'entité subit des dégats
 * Si la vie tombe a 0, on met l'entité sur sa sprite de destruction
 * et on supprime sa boundingbox
 * <*E> : l'entité qui subit des dégats
 * <damage> : montant de dégats que subit l'entité (-1 si l'entité doit mourir sur le coup)
 */
void getDamaged(Entity *E, int damage);

/*
 * getHealed
 * L'entité regagne de la vie
 * <*E> : l'entité qui regagne de la vie
 * <heal> : montant de vie regagnée
 */
void getHealed(Entity *E, int heal);

void executeRoutesEntityList(EntityList L, float xMax);

void executeRouteList(Entity *E);

int executeFirstRoute(Entity *E);

void initRouteListForEnnemyOne(Entity *E);

#endif
