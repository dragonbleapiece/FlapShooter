/*
 * shot.h
 * Déclaration des fonctions des projectiles
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef SHOT_H
#define SHOT_H

#include "settings.h"
#include "level.h"
#include "texture.h"

/*
 * entityShot
 * Génère un projectile dans la liste projectiles de <*level>
 * <E> : entité qui tire
 * <*level> : niveau où est généré le projectile
 * <sizeX> : taille en X du projectile
 * <sizeY> : taille en Y du projectile
 * <*t> : pointeur sur texture
 * <speedX> : vitesse en X du projectile
 * <speedY> : vitesse en Y du projectile
 * <boundingBox> : liste de bounding box du projectile
 */
void entityShot(Entity E, Level* level, float sizeX, float sizeY, Texture *t, float speedX, float speedY, BoundingBoxList boundingBox);

/*
 * playerShot
 * Génère un projectile du joueur dans la liste projectiles de <*level>
 * <*level> : niveau où est généré le projectile
 */
void playerShot(Level* level);

/*
 * ennemyOneShot
 * Génère un projectile d'un ennemi Un dans la liste projectiles de <*level>
 * <*level> : niveau où est généré le projectile
  * <*ennemy> : ennemi qui tire
 */
void ennemyOneShot(Level *level, Entity *ennemy);

/*
 * ennemiesShot
 * Génère les projectiles des ennemis dans la liste projectiles de <*level>
 * <*level> : niveau où est généré le projectile
  * <xMax> : position max en x des entités
 */
void ennemiesShot(Level *level, float xMax);

#endif
