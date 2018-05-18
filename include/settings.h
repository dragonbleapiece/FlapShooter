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


/* ----------------------- DEBUG ------------------------ */
#define SHOW_BOUNDING_BOX 0 /* Afficher les bounding box en violet sur les entités */
#define BOUNDING_BOX_COLOR 148,0,211,100 /* Couleur RGBA des bounding box */

/* -------------- DIMENSIONS DE LA FENETRE -------------- */

#define UNITE 37 /*Unite en px*/
#define RATIO 16/9

#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_WINDOW_WIDTH DEFAULT_WINDOW_HEIGHT*RATIO

/*
 * Nombre de décimal après la virgule pour les arrondie
 * Permet d'éviter les defauts d'affichages SDL
 */
#define ROUND_DECIMAL 100.

/* Nombre de bits par pixel de la fenêtre */
#define BIT_PER_PIXEL 32

/* Nombre minimal de millisecondes separant le rendu de deux images */
#define FPS 60
#define FRAMERATE_MILLISECONDS 1000 / FPS
#define SPRITES_PER_SECOND 30 /* Nombre de sprite par seconde */

/* ---------------------- BACKGROUND ---------------------- */

#define SRC_BACKGROUND0 SRC_RESOURCES_FOLDER "img/sky.jpg"
#define SRC_BACKGROUND1 SRC_RESOURCES_FOLDER "img/clouds.png"
#define SRC_BACKGROUND2 SRC_RESOURCES_FOLDER "img/mountains.png"
#define SRC_BACKGROUND3 SRC_RESOURCES_FOLDER "img/ground.png"

/* Taille en px */
#define MAX_HEIGHT_BACKGROUND 400 // Hauteur maximal des backgrounds pour prendre tout l'écran
#define HEIGHT_BACKGROUND0 400
#define WIDTH_BACKGROUND0 1200
#define HEIGHT_BACKGROUND1 400
#define WIDTH_BACKGROUND1 1200
#define HEIGHT_BACKGROUND2 134
#define WIDTH_BACKGROUND2 1200
#define HEIGHT_BACKGROUND3 40
#define WIDTH_BACKGROUND3 1200

/* ---------------------- TEXTURES ---------------------- */

#define SRC_RABBIT SRC_RESOURCES_FOLDER "img/rabbit.png"
#define SRC_OBSTACLE SRC_RESOURCES_FOLDER "img/obstacle.png"

/* ----------- Configuration des éléments du jeu ----------- */

#define LEVEL_SPEED 20 /* Vitesse du niveau par défaut (bloc par secondes) */

#define ACCELERATION 0.25

#define MAXSPEED 5

#define INERTIE 0.5

#define FREE_MOVES 2.0 / 3.0

#define BOUND 1.0 / 4.0

#endif
