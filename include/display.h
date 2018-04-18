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

#include "level.h"

typedef struct camera {
  float xMin,yMin; /* Position en bas à gauche de la caméra */
  float xMax,yMax; /* Position en haut à droite de la caméra */
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
 * <entity> : Pointeur sur l'entité
 */
void displayEntity(Entity* entity);

#endif