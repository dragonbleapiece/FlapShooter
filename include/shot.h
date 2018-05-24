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
 * playerShot
 * Génère un projectile dans la liste projectiles de <*level>
 * <E> : entity qui tire
 * <*level> : niveau où est généré le projectile
 */
void entityShot(Entity E, Level* level, float sizeX, float sizeY, Texture *t, float speedX, float speedY, BoundingBoxList boundingBox);

void playerShot(Level* level);

void ennemyOneShot(Level *level, Entity *ennemy);

void ennemiesShot(Level *level, float xMax);

#endif
