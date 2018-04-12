/*
 * bounding.h
 * Déclaration de la structure et des fonctions de gestion des bounding box et de leurs forme
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef BOUNDING_H
#define BOUNDING_H

#include <stdlib.h>
#include <stdio.h>

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
  ShapeType type; /* Sélecteur de la forme de la bounding box */
  BoundingShape shape; /* Forme de la bounding box dans le repère de l'entité (ex: 0, 0 pour le point en bas a gauche) */
  struct boundingBox* next;
} BoundingBox, *BoundingBoxList;

/*
 * allocBoundingBox
 * Alloue une entité dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <shape> : Forme de la bounding box (structure AABB ou Circle)
 * <type> : Type de la forme (AABB_SHAPE, CIRCLE_SHAPE)
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* allocBoundingBox(BoundingShape shape, ShapeType type);

/*
 * addBoundingBoxToList
 * Ajoute la BoundingBox <*B> au début de la liste <*L>
 * <*L> : Pointeur de la liste de BoundingBox
 * <*E> : BoundingBox a ajouter, supposé dans aucune liste
 */
void addBoundingBoxToList(BoundingBoxList *L, BoundingBox *B);

/*
 * convertShapeToAbsolute
 * Converti les coordonnées relatif d'une forme en coordonnées absolu
 * <shape> : Forme de la bounding box (structure AABB ou Circle)
 * <type> : Type de la forme (AABB_SHAPE, CIRCLE_SHAPE)
 * <x> et <y> : Coordonnées de position en bas a gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne la structure de la forme en coordonnées absolu
 */
BoundingShape convertShapeToAbsolute(BoundingShape shape, ShapeType type, float x, float y, float sizeX, float sizeY);

/*
 * convertAABBtoAbsolute
 * Converti les coordonnées relatif d'un AABB en coordonnées absolu
 * <box> : La structure AABB en coordonnées relatif
 * <x> et <y> : Coordonnées de position en bas a gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne une structure AABB en coordonnées absolu
 */
AABB convertAABBtoAbsolute(AABB box, float x, float y, float sizeX, float sizeY);

/*
 * convertCircletoAbsolute
 * Converti les coordonnées relatif d'un cercle en coordonnées absolu
 * <circle> : La structure AABB en coordonnées relatif
 * <x> et <y> : Coordonnées de position en bas a gauche de l'entité
 * <sizeX> et <sizeY> : Hauteur et largeur de l'entité
 * Retourne une structure Circle en coordonnées absolu
 */
Circle convertCircleToAbsolute(Circle circle, float x, float y, float sizeX, float sizeY);

/*
 * convertCircletoAABB
 * Retourne l'AABB qui encadre le cercle <circle>
 */
AABB convertCircleToAABB(Circle circle);

/*
 * isCollidingShape
 * Teste si la forme <S1> et en collision avec la forme <S2> (supposé dans le même référentiel)
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
 * Calcul la projection de C sur (AB) et teste si elle appartient a [AB]
 * <Cx> et <Cy> : Cordonnée x et y de C
 * <Ax> et <Ay> : Cordonnée x et y de A
 * <Bx> et <By> : Cordonnée x et y de B
 * Retourne 1 si la projection appartient a [AB], 0 sinon
 */
int projectionOnSegment(int Cx, int Cy, int Ax, int Ay, int Bx, int By);


#endif
