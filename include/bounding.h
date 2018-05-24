/*
 * bounding.h
 * Déclaration de la structure et des fonctions de gestion des bounding box et de leurs formes
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef BOUNDING_H
#define BOUNDING_H

#include <stdlib.h>
#include <stdio.h>
#include "settings.h"

typedef struct {
  float xMin, yMin; /* Point en bas à gauche du carré */
  float xMax, yMax; /* Point en haut à droite du carré */
} AABB;

typedef struct {
  float x, y; /* Centre du cercle */
  float r; /* Rayon du cercle */
} Circle;

typedef enum {
  AABB_SHAPE,
  CIRCLE_SHAPE
} ShapeType;

typedef union BoundingShape BoundingShape;

union BoundingShape {
  AABB box;
  Circle circle;
};

typedef struct boundingBox {
  /* Sélecteur de la forme de la bounding box */
  ShapeType type;
  /* 
   * Forme de la bounding box dans le repère de l'entité 
   *  - (0,0) pour le point en bas à gauche
   *  - (1,1) pour le point en haut à droite
   */
  BoundingShape shape;
  struct boundingBox* next;
} BoundingBox, *BoundingBoxList;

/*
 * allocBoundingBox
 * Alloue une BoundingBox dans l'espace mémoire et initialise ses paramètres
 * Quitte le programme en cas d'erreur d'allocation
 * <shape> : Forme de la bounding box (structure AABB ou Circle)
 * <type> : Type de la forme (AABB_SHAPE, CIRCLE_SHAPE)
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* allocBoundingBox(BoundingShape shape, ShapeType type);

/*
 * freeBoundingBoxList
 * Libère la mémoire occupée par toutes les bounding box de la liste <*L>
 * <*L> : Pointeur de la liste de bounding box
 */
void freeBoundingBoxList(BoundingBoxList *L);

/*
 * addBoundingBoxToList
 * Ajoute la BoundingBox <*B> au début de la liste <*L>
 * <*L> : Pointeur de la liste de BoundingBox
 * <*E> : BoundingBox à ajouter, supposée dans aucune liste
 */
void addBoundingBoxToList(BoundingBoxList *L, BoundingBox *B);

/*
 * createAABBBoundingBox
 * Crée et alloue une BoundingBox AABB, centrée sur le milieu,
 * de hauteur <h> et de largeur <w>
 * <w> : Largeur dans le repère de l'entité (ex: 1 = taille de l'entité)
 * <h> : Hauteur dans le repère de l'entité (ex: 1 = taille de l'entité)
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* createAABBBoundingBox(float w, float h);

/*
 * createSquareBoundingBox
 * Crée et alloue une BoundingBox AABB carré, 
 * centrée sur le milieu et de hauteur <size>
 * <size> : Taille dans le repère de l'entité (ex: 1 = taille de l'entité)
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* createSquareBoundingBox(float size);

/*
 * createCircleBoundingBox
 * Crée et alloue une BoundingBox circulaire, 
 * centrée sur le milieu et de rayon <radius>
 * <radius> : Rayon dans le repère de l'entité (ex: 1 = taille de l'entité)
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* createCircleBoundingBox(float radius);

/*
 * createCapsuleBoundingBox
 * Crée et alloue une BoundingBox type capsule collider, centrée sur le milieu,
 * de hauteur <h> et de largeur <w>
 * <w> : Largeur dans le repère de l'entité (ex: 1 = taille de l'entité)
 * <h> : Hauteur dans le repère de l'entité (ex: 1 = taille de l'entité)
 * Retourne un pointeur sur la BoundingBox (BoundingBoxList de 3 éléments)
 */
BoundingBox* createCapsuleBoundingBox(float w, float h);

/*
 * convertShapeToAbsolute
 * Convertit les coordonnées relatives d'une forme en coordonnées absolues
 * <shape> : Forme de la bounding box (structure AABB ou Circle)
 * <type> : Type de la forme (AABB_SHAPE, CIRCLE_SHAPE)
 * <x> et <y> : Coordonnées de position en bas à gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne la structure de la forme en coordonnées absolues
 */
BoundingShape convertShapeToAbsolute(BoundingShape shape, ShapeType type, float x, float y, float sizeX, float sizeY);

/*
 * convertAABBtoAbsolute
 * Convertit les coordonnées relatives d'un AABB en coordonnées absolues
 * <box> : La structure AABB en coordonnées relatives
 * <x> et <y> : Coordonnées de position en bas à gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne une structure AABB en coordonnées absolues
 */
AABB convertAABBtoAbsolute(AABB box, float x, float y, float sizeX, float sizeY);

/*
 * convertCircletoAbsolute
 * Convertit les coordonnées relatives d'un cercle en coordonnées absolues
 * <circle> : La structure AABB en coordonnées relatives
 * <x> et <y> : Coordonnées de position en bas à gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne une structure Circle en coordonnées absolues
 */
Circle convertCircleToAbsolute(Circle circle, float x, float y, float sizeX, float sizeY);

/*
 * convertCircletoAABB
 * Retourne l'AABB qui encadre le cercle <circle>
 */
AABB convertCircleToAABB(Circle circle);

/*
 * isCollidingShape
 * Teste si la forme <S1> et en collision avec la forme <S2> (supposée dans le même référentiel)
 * <S1> : Première forme (structure AABB ou Circle)
 * <type1> : Type de la première forme (AABB_SHAPE, CIRCLE_SHAPE)
 * <S2> : Deuxieme forme (structure AABB ou Circle)
 * <type2> : Type de la deuxieme forme (AABB_SHAPE, CIRCLE_SHAPE)
 * Retourne 1 si collision, 0 sinon
 */
int isCollidingShape(BoundingShape S1, ShapeType type1, BoundingShape S2, ShapeType type2);

/*
 * isCollidingAABB
 * Teste si les AABB <B1> et <B2> sont en collision
 * Retourne 1 si collision, 0 sinon
 */
int isCollidingAABB(AABB B1, AABB B2);

/*
 * isCollidingCircle
 * Teste si les cercles <C1> et <C2> sont en collision
 * Retourne 1 si collision, 0 sinon
 */
int isCollidingCircle(Circle C1, Circle C2);

/*
 * isCollidingAABBandCircle
 * Teste si le AABB <B> et le clercle <C> sont en collision
 * Retourne 1 si collision, 0 sinon
 */
int isCollidingAABBandCircle(AABB B, Circle C);

/*
 * isCollidingCircleandPoint
 * Teste si les coordonnées sont comprises dans le cercle <C>
 * <x> : coordonnée en x
 * <y> : coordonnée en y
 * <C> : le cercle
 * Retourne 1 si les coordonnées sont comprises, 0 sinon
 */
int isCollidingPointAndCircle(float x, float y, Circle C);

/*
 * isCollidingPointAndAABB
 * Teste si les coordonnées sont comprises au sein du AABB <box>
 * <x> : coordonnée en x
 * <y> : coordonnée en y
 * <box> : le AABB
 * Retourne 1 si les coordonnées sont comprises, 0 sinon
 */
int isCollidingPointAndAABB(float x, float y, AABB box);

/*
 * projectionOnSegment
 * Calcule la projection de C sur (AB) et teste si elle appartient à [AB]
 * <Cx> et <Cy> : Cordonnées x et y de C
 * <Ax> et <Ay> : Cordonnées x et y de A
 * <Bx> et <By> : Cordonnées x et y de B
 * Retourne 1 si la projection appartient à [AB], 0 sinon
 */
int projectionOnSegment(int Cx, int Cy, int Ax, int Ay, int Bx, int By);


#endif
