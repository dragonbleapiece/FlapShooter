/*
 * entity.h
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef ENTITY_H
#define ENTITY_H
#include "settings.h"
#include "bounding.h"
#include "texture.h"


typedef enum entityCode {
  VOID_CODE,
  PLAYER_CODE,
  ENNEMYONE_CODE,
  ENNEMYTWO_CODE,
  OBSTACLE_CODE,
  DESTRUCTIBLE_CODE,
  BONUS_CODE,
  PROJECTILE_CODE,
  END_CODE
} EntityCode;

typedef struct entity {
  float x, y; /* Coordonnées de position en bas a gauche de l'entité */
  float sizeX, sizeY; /* Hauteur et largeur de l'entité */
  Texture *texture;
  float speedX;
  float speedY;
  float shotFrequency;
  int xTextureIndice; /* Division vertical actuel de l'image pour les sprites, 0 par défaut (1er sprite) */
  int yTextureIndice; /* Division horizontal actuel de l'image pour les "sprites",  0 par défaut (1er sprite) */
  int life; /* Vie actuelle de l'entité, -1 si invincible */
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
Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, Texture *texture, BoundingBoxList boundingBox);

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
 */
void removeEntityBehind(EntityList *L, float xMax);

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

#endif
