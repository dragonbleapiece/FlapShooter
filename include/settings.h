/*
 * settings.h
 * Déclaration des paramètres : variables globales
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define CERCLE_LIGNES 50 /* Nombre de polygones d'un cercle */

#define UNTEXTURED_BOX_COLOR 255,0,255,255 /* Couleur RGBA des objets non texturés */

#define SRC_RESOURCES_FOLDER "assets/"

/* ----------------------- DEBUG ------------------------ */
#define SHOW_BOUNDING_BOX 0 /* Afficher les bounding box en violet sur les entités */
#define BOUNDING_BOX_COLOR 148,0,211,100 /* Couleur RGBA des bounding box */

/* -------------- DIMENSIONS DE LA FENETRE -------------- */

#define UNITE 37 /*Unité en px*/
#define RATIO 16/9 /* Ratio de la résolution de l'écran */

#define DEFAULT_WINDOW_HEIGHT 720 /* Hauteur par défaut de la fenêtre */
#define DEFAULT_WINDOW_WIDTH DEFAULT_WINDOW_HEIGHT*RATIO /* Largeur par défaut de la fenêtre */

/*
 * Nombre de décimales après la virgule pour les arrondis
 * Permet d'éviter les defauts d'affichage SDL
 */
#define ROUND_DECIMAL 100.

/* Nombre de bits par pixel de la fenêtre */
#define BIT_PER_PIXEL 32

/* Nombre minimal de millisecondes séparant le rendu de deux images */
#define FPS 60
#define FRAMERATE_MILLISECONDS 1000 / FPS
#define SPRITES_PER_SECOND 30 /* Nombre de sprites par seconde */

/* ---------------------- BACKGROUND ---------------------- */

#define SRC_BACKGROUND0 SRC_RESOURCES_FOLDER "img/sky.jpg"
#define SRC_BACKGROUND1 SRC_RESOURCES_FOLDER "img/clouds.png"
#define SRC_BACKGROUND2 SRC_RESOURCES_FOLDER "img/mountains.png"
#define SRC_BACKGROUND3 SRC_RESOURCES_FOLDER "img/ground.png"

/* Taille en px */
#define MAX_HEIGHT_BACKGROUND 400 // Hauteur maximale des backgrounds pour prendre tout l'écran
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
#define SRC_RATON SRC_RESOURCES_FOLDER "img/raton.png"
#define SRC_SPEED_BONUS SRC_RESOURCES_FOLDER "img/speed_egg.png"
#define SRC_SHOT_BONUS SRC_RESOURCES_FOLDER "img/shoot_egg.png"
#define SRC_HEART SRC_RESOURCES_FOLDER "img/heart.png"
#define SRC_DESTRUCTIBLE_OBSTACLE SRC_RESOURCES_FOLDER "img/wood_box.png"
#define SRC_OBSTACLE SRC_RESOURCES_FOLDER "img/obstacle.png"
#define SRC_CARROTBALL SRC_RESOURCES_FOLDER "img/carrotball.png"
#define SRC_PIP SRC_RESOURCES_FOLDER "img/pip.png"
#define SRC_WIN_UI SRC_RESOURCES_FOLDER "img/win_ui.png"
#define SRC_LOSE_UI SRC_RESOURCES_FOLDER "img/lose_ui.png"

/* ----------- Configuration des éléments du jeu ----------- */

#define LEVEL_SPEED 5 /* Vitesse du niveau par défaut (blocs par secondes) */

#define ACCELERATION 1

#define MAXSPEED 5

#define INERTIE 2

#define FREE_MOVES 2.0 / 3.0

#define BOUND 1.0 / 4.0

#define PROJECTILE_SPEED 15

#define PLAYER_SHOT_FREQUENCY 0.5

#define SPEED_BONUS_DURATION 5 /* en secondes */
#define SPEED_BONUS_COEFF 2 /* Multiplication de la vitesse pendant ce bonus */

#define SHOT_BONUS_DURATION 5 /* en secondes */
#define SHOT_BONUS_COEFF 4 /* Multiplication de la vitesse pendant ce bonus */

#define ENNEMYONE_MOVE_X 0
#define ENNEMYONE_MOVE_Y 0.5
#define ENNEMYONE_MOVE_DURATION 1

#define ENNEMY_SHOT_FREQUENCY 0.2

#define ENNEMY_SPAWN_SHOT 0.8

#endif
