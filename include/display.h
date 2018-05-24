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
#include "UI.h"

typedef struct camera {
  float xMin, yMin; /* Position en bas à gauche de la caméra */
  float xMax, yMax; /* Position en haut à droite de la caméra */
} Camera;

/*
 * displayLevel
 * Affiche toutes les entités d'un niveau qui sont dans le champs de la caméra
 * Appelée à chaque frame
 * <*lvl> : Structure du niveau
 * <cam> : Structure de la caméra
 */
void displayLevel(Level *lvl, Camera cam);

/*
 * displayEntity
 * Affiche une entité
 * Affiche également sa bounding box si l'option est activée dans settings.h
 * <*E> : Pointeur sur l'entité
 * <xRelative> : position relative en x
 * <yRelative> : position relative en y
 */
void displayEntity(Entity* E, float xRelative, float yRelative);

/*
 * displayTexturedEntity
 * Affiche une entité avec sa texture
 * Affiche également sa bounding box si l'option est activée dans settings.h
 * <*E> : Pointeur sur l'entité
 * <xRelative> : position relative en x
 * <yRelative> : position relative en y
 */
void displayTexturedEntity(Entity* E, float xRelative, float yRelative);

/*
 * displayEntityList
 * Affiche toutes les entités d'une liste jusqu'à <xMax>
 * Gère les destructions d'entités si elles arrivent à la dernière sprite de destruction
 * <*L> : Pointeur sur la liste triée des entités
 * <xMax> : Coordonnée maximum en x des entités à afficher
 * <nextSprite> : afficher la sprite suivante (0 = non, 1 = oui)
 */
void displayEntityList(EntityList *L, float xMax, int nextSprite);

/*
 * displayEntityBackgroundList
 * Affiche toutes les entités de décors
 * Gère l'effet parallaxe et la répétition
 * <*L> : Pointeur sur la liste triée des entités
 * <xMin> : Coordonnée minimum en x des entités
 * <nextSprite> : Afficher la sprite suivante (0 = non, 1 = oui)
 * <spedd> : la vitesse du niveau
 */
void displayEntityBackgroundList(EntityList *L, float xMin, int nextSprite, float speed);

/*
 * displayBoundingBox
 * Affiche une bounding box en transparence par rapport à son entité
 * <*B> : Pointeur sur la bounding box
 * <*E> : Pointeur sur l'entité
 */
void displayBoundingBox(BoundingBox *B, Entity* E);

/*
 * displayBoundingBoxList
 * Affiche toutes les bounding box d'une liste en transparence par rapport à leurs entités
 * <L> : La liste des bounding box
 * <*E> : Pointeur sur l'entité
 */
void displayBoundingBoxList(BoundingBoxList L, Entity* E);

/*
 * initCamera
 * Initialise les valeurs de la caméra
 * <height> : Nombre d'unités verticales
 * Retourne une structure Camera avec les valeurs initialisées
 */
Camera initCamera(int height);

/*
 * translateCamera
 * Déplace la caméra <*cam> de <x> et <y> pixels
 * <*cam> : Camera à déplacer
 * <x> : Déplacement en x de la caméra
 * <y> : Déplacement en y de la caméra
 */
void translateCamera(Camera *cam, float x, float y);

/*
 * displayEntityListOnCam
 * Affiche toutes les entités d'une liste relative aux positions de la caméra
 * Gère les destructions d'entités si elles arrivent à la dernière sprite de destruction
 * <*L> : Pointeur sur la liste triée des entités
 * <cam> : Caméra sur laquelle on affiche
 * <nextSprite> : Afficher la sprite suivante (0 = non, 1 = oui)
 */
void displayEntityListOnCam(EntityList *L, Camera cam, int nextSprite);

/*
 * displayEntityHeartsUi
 * Affiche l'interface de la vie de l'utilisateur
 * <*interface> : Pointeur sur l'interface
 * <numbers> : Nombre de coeurs à afficher
 * <cam> : Camera sur laquelle on affiche
 */
void displayEntityHeartsUi(UI *interface, int numbers, Camera cam);

/*
 * displayEntityEndScreenUi
 * Affiche l'écran de fin du jeu en fonction de playerStatus
 * <*interface> : Pointeur sur l'interface
 * <playerStatus> : Statuts du joueur
 * <cam> : Caméra sur laquelle on affiche
 */
void displayEntityEndScreenUi(UI *interface, int playerStatus, Camera cam);

/*
 * displayUILevel
 * Affiche tous les éléments de l'interface en fonction de l'état du niveau
 * <*interface> : Pointeur sur l'interface
 * <cam> : Caméra sur laquelle on affiche
 * <level> : Structure du niveau actuel
 */
void displayUILevel(UI *interface, Camera cam, Level level);



#endif
