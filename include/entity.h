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
  float x, y; /* Coordonnées de position en haut à gauche de l'entité */
  float sizeX, sizeY; /* Hauteur et largeur de l'entité */
  Texture *texture;
  float speedX;
  float speedY;
  float shotX;
  float shotY;
  Uint32 lastShot;
  float shotFrequency;
  int xTextureIndice; /* Division horizontale actuelle de l'image pour les "sprite"s, 0 par défaut (1ere sprite) */
  int yTextureIndice; /* Division verticale actuelle de l'image pour les "sprites",  0 par défaut (1ere sprite) */
  int life; /* Vie actuelle de l'entité, -1 si invincible */
  int maxLife; /* Vie maximale de l'entité */
  int attack; /* Point d'attaque de l'entité */
  EntityCode entityCode;
  RouteList routes; /* Liste triée par id des routes */
  BoundingBoxList boundingBox; /* Pointeur sur la liste de bounding box de l'entité */
  struct entity* next; /* Pointeur sur l'entité suivante dans la liste */
} Entity, *EntityList;

/*
 * allocEntity
 * Alloue une entité dans l'espace mémoire et initialise ses paramètres
 * Quitte le programme en cas d'erreur d'allocation
 * <x> : Position x de l'entité
 * <y> : Position y de l'entité
 * <sizeX> : Largeur de l'entité
 * <sizeY> : Hauteur de l'entité
 * <maxLife> : Vie maximale et actuelle de l'entité
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
 * <*L> : Pointeur de la liste triée d'entités
 * <*E> : Entité à ajouter, supposée dans aucune liste
 */
void addEntityToList(EntityList *L, Entity *E);

/*
 * addEntityToUnsortedList
 * Ajoute l'entité <*E> à la liste <*L> sans la trier, à la dernière position
 * <*L> : Pointeur de la liste d'entités
 * <*E> : Entité à ajouter, supposée dans aucune liste
 */
void addEntityToUnsortedList(EntityList *L, Entity *E);

/*
 * printEntityList
 * Affiche récursivement la liste d'entités pour debugage
 * <L> : Pointeur de la liste triée d'entités
 */
void printEntityList(EntityList L);

/*
 * removeEntityToList
 * Enlève l'entité <E> de la liste <*L> et libère la mémoire occupée
 * par l'entité et ses Bounding Box
 * <*L> : Pointeur de la liste triée d'entités
 * <E> : Entité à supprimer, supposée dans la liste
 * retourne 1 si l'entité a été enlevée, 0 sinon
 */
int removeEntityToList(EntityList *L, EntityList E);

/*
 * removeEntityBehind
 * Enlève toutes les entités de la liste <*L> jusqu'à xMax
 * et libère la mémoire occupée. Prend en compte la taille des entités.
 * <*L> : Pointeur de la liste triée d'entités
 * <xMax> : Coordonnée maximum en x des entités à supprimer
 */
void removeEntityBehind(EntityList *L, float xMax);

/*
 * removeEntityInFront
 * Enlève toutes les entités de la liste <*L> après xMax
 * et libère la mémoire occupée. Prend en compte la taille des entités.
 * <*L> : Pointeur de la liste triée d'entités
 * <xMax> : Coordonnée minimum en x des entités à supprimer
 */
void removeEntityInFront(EntityList *L, float xMax);

/*
 * freeEntity
 * Libère la mémoire occupée par l'entité <*E>
 * <*E> : Pointeur de l'entité
 */
void freeEntity(Entity *E);

/*
 * freeEntityList
 * Libère la mémoire occupée par toutes les entités de la liste <*L>
 * <*L> : Pointeur de la liste triée d'entités
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
 * Si on est à la fin de la ligne, la sprite revient à l'état de repos (0,0)
 * <*E> : Entité à modifier
 * Retourne 1 si on est revenu à l'état de repos, 0 sinon
 */
int upXSpriteEntity(Entity *E);

/*
 * setSpriteEntity
 * Redéfinit la sprite actuelle de l'entité
 * <*E> : Entité à modifier
 * <x> : Nouvelle division horizontale de l'image pour les sprites, 0 = 1ere sprite
 * <y> : Nouvelle division verticale de l'image pour les sprites, 0 = 1ere sprite
 * Retourne 0 si la nouvelle sprite n'existe pas, 1 sinon
 */
int setSpriteEntity(Entity *E, int x, int y);

/*
 * translateEntity
 * Déplace l'entité <*E> de <x> et <y> unité
 * <*E> : Entité à déplacer
 * <x> : Déplacement en x de l'entité
 * <y> : Déplacement en y de l'entité
 */
void translateEntity(Entity *E, float x, float y);

/*
 * translateEntityList
 * Déplace toutes les entités de la liste <L> de <x> et <y> unité
 * <L> : La liste d'entités à déplacer
 * <x> : Déplacement en x de l'entité
 * <y> : Déplacement en y de l'entité
 * <xMax> : Coordonnée maximum en x des entités à déplacer
 */
void translateEntityList(EntityList L, float x, float y, float xMax);

/*
 * translateEntityBySpeed
 * Déplace l'entité <*E> par son vecteur vitesse
 * N.B. les entités dont la vie est à 0 ne sont pas déplacées
 * <*E> : Entité à déplacer
 */
void translateEntityBySpeed(Entity *E);

/*
 * translateEntityListBySpeed
 * Déplace toutes les entités de la liste <L> par leurs vecteurs vitesse
 * <L> : La liste d'entités à déplacer
 * <xMax> : Coordonnée maximum en x des entités à déplacer
 */
void translateEntityListBySpeed(EntityList L, float xMax);

/*
 * attacks
 * Attaque d'une entité sur une autre
 * <*E1> : entité qui attaque
 * <*E2> : entité qui subit l'attaque
 */
void attacks(Entity *E1, Entity *E2);

/*
 * attacksBetween
 * Attaque réciproque d'une entité sur une autre
 * <*E1> : entité impliquée
 * <*E2> : entité impliquée
 */
void attacksBetween(Entity *E1, Entity *E2);

/*
 * getDamaged
 * L'entité subit des dégats
 * Si la vie tombe à 0, on met l'entité sur sa sprite de destruction
 * et on supprime sa boundingbox
 * <*E> : l'entité qui subit des dégats
 * <damage> : montant des dégats que subit l'entité (-1 si l'entité doit mourir sur le coup)
 */
void getDamaged(Entity *E, int damage);

/*
 * getHealed
 * L'entité regagne de la vie
 * <*E> : l'entité qui regagne de la vie
 * <heal> : montant de vies regagnées
 */
void getHealed(Entity *E, int heal);

/*
 * executeRoutesEntityList
 * exécute les routes de la liste d'entités
 * <L> : liste d'entités
 * <xMax> : position max des entités
 */
void executeRoutesEntityList(EntityList L, float xMax);

/*
 * executeRouteList
 * exécute les routes d'une entité
 * <*E> : pointeur sur l'entité
 */
void executeRouteList(Entity *E);

/*
 * executeFirstRoute
 * exécute la route de l'entité
 * <*E> : pointeur sur l'entité
 * Retourne -1 si la route est NULL, 1 si la route est en cours d'exécution, 0 sinon
 */
int executeFirstRoute(Entity *E);

/*
 * initRouteListForEnnemyOne
 * initialise la liste de routes pour l'ennemi un
 * <*E> : pointeur sur l'entité
 */
void initRouteListForEnnemyOne(Entity *E);

#endif
