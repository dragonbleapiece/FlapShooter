/*
 * settings.h
 * Déclaration des paramètres : variables globales et statiques
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define CERCLE_LIGNES 50 /* Nombre de polygones d'un cercle */

#define UNTEXTURED_BOX_COLOR 255,0,255,255 /* Couleur RGBA des objets non texturé */

#define SRC_RESOURCES_FOLDER "assets/"



#define UNITE 37 /*Unite en px*/

/* DEBUG */
#define SHOW_BOUNDING_BOX 1 /* Afficher les bounding box en violet sur les entités */
#define BOUNDING_BOX_COLOR 148,0,211,100 /* Couleur RGBA des bounding box */

/* Dimensions de la fenêtre */
#define WINDOW_WIDTH 814
#define WINDOW_HEIGHT 407

/* Nombre de bits par pixel de la fenêtre */
#define BIT_PER_PIXEL 32

/* Nombre minimal de millisecondes separant le rendu de deux images */
#define FRAMERATE_MILLISECONDS 1000 / 60
#define SPRITES_PER_SECOND 30 /* Nombre de sprite par seconde */

/* ---------------------- BACKGROUND ---------------------- */

#define SRC_BACKGROUND1 SRC_RESOURCES_FOLDER "img/sky.png"
#define SRC_BACKGROUND2 SRC_RESOURCES_FOLDER "img/mountains.png"
#define SRC_BACKGROUND3 SRC_RESOURCES_FOLDER "img/ground.png"

#define HEIGHT_BACKGROUND1 WINDOW_HEIGHT
#define WIDTH_BACKGROUND1 WINDOW_HEIGHT*3
#define HEIGHT_BACKGROUND2 WINDOW_HEIGHT/3
#define WIDTH_BACKGROUND2 WINDOW_HEIGHT*3
#define HEIGHT_BACKGROUND3 WINDOW_HEIGHT/10
#define WIDTH_BACKGROUND3 WINDOW_HEIGHT*3

/* ---------------------- TEXTURES ---------------------- */

#define SRC_RABBIT SRC_RESOURCES_FOLDER "img/rabbit.png"

/* ----------- Configuration des éléments du jeu ----------- */

#define LEVEL_SPEED 1

#define ACCELERATION 0.25

#define MAXSPEED 5

#define INERTIE 0.5

#define FREE_MOVES 2.0 / 3.0

#define BOUND 1.0 / 4.0

#endif
