/*
 * settings.h
 * Déclaration des paramètres : variables globales et statiques
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef SETTINGS_H
#define SETTINGS_H


#define RGBA_EXTENSION (const char *[3]){"png","gif","bpm"} /* Les différentes extensions des images en RGBA */
#define RGBA_EXTENSION_SIZE (int) 3 /* Taille du tableau ci-dessus */

#define CERCLE_LIGNES 50 /* Nombre de polygones d'un cercle */

#define UNTEXTURED_BOX_COLOR 255,0,255,255 /* Couleur RGBA des objets non texturé */

#define SPRITES_PER_SECOND 30 /* Nombre de sprite par seconde */

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

/* ------------------- Configuration des éléments du jeu */

#define LEVEL_SPEED 1

#define ACCELERATION 0.25

#define MAXSPEED 5

#define INERTIE 0.5

#define FREE_MOVES 2.0 / 3.0

#define BOUND 1.0 / 4.0

#endif
