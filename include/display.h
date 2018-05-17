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
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
 * Appelé à chaque frame
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
 * <*L> : Pointeur sur la liste triée des entités
 * <xMax> : Coordonnée maximum en x des entités a afficher
 * <nextSprite> : afficher la sprite suivante (0 = non, 1 = oui)
 */
void displayEntityList(EntityList *L, float xMax, int nextSprite);

/*
 * displayEntityBackgroundList
 * Affiche toutes les entités de décors
 * Gère l'effet paralaxe et la répétition
 * <*L> : Pointeur sur la liste triée des entités
 * <xMin> : Coordonnée minimum en x des entités
 * <nextSprite> : afficher la sprite suivante (0 = non, 1 = oui)
 */
void displayEntityBackgroundList(EntityList *L, float xMin, int nextSprite);

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

/*
 * initCamera
 * Initialise les valeurs de la caméra
 * Retourne une structure Camera avec les valeurs initialisées
 */
Camera initCamera();

/*
 * translateCamera
 * Déplace la camera <*cam> de <x> et <y> pixels
 * <*cam> : Camera a déplacer
 * <x> : Déplacement en x de la caméra
 * <y> : Déplacement en y de la caméra
 */
void translateCamera(Camera *cam, float x, float y);

#endif
