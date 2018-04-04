/*
 * bounding.h
 * Déclaration de la structure et des fonctions de gestion des bounding box
 * 
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef BOUNDING_H
#define BOUNDING_H

#include <stdlib.h>
#include <stdio.h>

typedef enum boundingShape {
  BOUNDING_SQUARE = 's',
  BOUNDING_CIRCLE = 'c'
} BoundingShape;

typedef struct boundingBox {
  float xMin, yMin; /* Point en bas à gauche de la bounding box relatif a l'entité */
  float xMax, yMax; /* Point en haut à droite de la bounding box relatif a l'entité */
  BoundingShape shape; /* Forme de la bounding box */
  struct boundingBox* next;
} BoundingBox, *BoundingBoxList;

/*
 * allocBoundingBox
 * Alloue une entité dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <xMin> : Position x du point en bas à gauche de la bounding box relatif a l'entité
 * <yMin> : Position y du point en bas à gauche de la bounding box relatif a l'entité
 * <xMax> : Position x du point en haut à droite de la bounding box relatif a l'entité
 * <yMax> : Position y du point en haut à droite de la bounding box relatif a l'entité
 * <shape> : Forme de la bounding box
 * Retourne un pointeur sur la BoundingBox
 */
BoundingBox* allocBoundingBox(float xMin, float yMin, float xMax, float yMax, BoundingShape shape);

/*
 * addBoundingBoxToList
 * Ajoute la BoundingBox <*B> à la liste <*L> 
 * <*L> : Pointeur de la liste de BoundingBox
 * <*E> : BoundingBox a ajouter, supposé dans aucune liste
 */
void addBoundingBoxToList(BoundingBoxList *L, BoundingBoxList *B);

#endif