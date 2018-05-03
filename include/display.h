/*
 * display.h
 * Déclaration de la structure et des fonctions de gestion de l'affichage
 * 
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "settings.h"

#include "level.h"

typedef struct camera {
  float xMin, yMin; /* Position en bas à gauche de la caméra */
  float xMax, yMax; /* Position en haut à droite de la caméra */
} Camera;

/*
 * displayLevel
 * Affiche toutes les entités d'un niveau qui sont dans le champs de la camera
 * <lvl> : Structure du niveau
 * <cam> : Structure de la camera 
 */
void displayLevel(Level lvl, Camera cam);

/*
 * displayEntity
 * Affiche une entité
 * Affiche également sa bounding box si l'option est activé dans settings.h
 * <*E> : Pointeur sur l'entité
 */
void displayEntity(Entity* E);

/*
 * displayTexturedEntity
 * Affiche une entité avec sa texture
 * Affiche également sa bounding box si l'option est activé dans settings.h
 * <*E> : Pointeur sur l'entité
 */
void displayTexturedEntity(Entity* E);

/*
 * displayEntityList
 * Affiche toutes les entités d'une liste jusqu'à <xMax> 
 * Gère les destructions d'entité si elles arrivent à la dernière sprite de destruction
 * <L> : La liste triée des entités
 * <maxX> : Coordonnée maximum en x des entités a afficher
 * <nextSprite> : afficher la sprite suivante (0 = non, 1 = oui)
 */
void displayEntityList(EntityList L, float xMax);//, int nextSprite);

/*
 * displayBoundingBox
 * Affiche une bounding box en transparance par rapport a son entité
 * <*B> : Pointeur sur la bounding box
 * <*E> : Pointeur sur l'entité
 */
void displayBoundingBox(BoundingBox *B, Entity* E);

/*
 * displayBoundingBoxList
 * Affiche toutes les bounding box d'une liste en transparance par rapport a leur entité
 * <L> : La liste des bounding box
 * <*E> : Pointeur sur l'entité
 */
void displayBoundingBoxList(BoundingBoxList L, Entity* E);


#endif