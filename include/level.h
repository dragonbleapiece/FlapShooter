/*
 * level.h
 * Déclaration de la structure et des fonctions de gestion des niveaux
 * 
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"

typedef struct level {
  EntityList player;
  EntityList obstacles;
  EntityList ennemies;
  EntityList bonus;
  EntityList projectiles;
} Level;

/*
 * generateLevelFromFile
 * Génére toutes les entités d'un niveau depuis un fichier PPM
 * <fileName[]> : nom du fichier au format PPM décrivant le niveau
 * Retourne une structure Level
 */
Level generateLevelFromFile(char fileName[]);

/*
 * freeLevel
 * Libére la mémoire occupée par toutes les listes du niveau
 * <*L> : Pointeur de la liste triée d'entité
 */
void freeLevel(Level L);

#endif