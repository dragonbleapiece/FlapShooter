/*
 * level.h
 * Déclaration de la structure et des fonctions de gestion des niveaux
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef LEVEL_H
#define LEVEL_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "entity.h"
#include "ppm.h"
#include "settings.h"
#include "bounding.h"
#include "collision.h"
#include "tools.h"
#include "bonus.h"

typedef struct level {
  EntityList player; /* Pointeur sur l'entité joueur */
  EntityList obstacles; /* Liste triée d'entités obstacles */
  EntityList ennemies; /* Liste triée d'entités ennemis */
  EntityList bonus; /* Liste triée d'entités bonus */
  EntityList projectiles; /* Liste triée d'entités projectiles */
  EntityList background; /* liste NON triée des éléments du background */
  TextureList textures; /* Liste triée contenant toutes les textures utilisées */
  BonusList currentBonus; /* Liste des bonus actifs */
  int height, width;
  float speed;
  float speedCoeff;
  int playerStatus; /* Status du joueur : 1= en jeu, 2 = gagnant, 0 = mort */
} Level;

/*
 * generateLevelFromFile
 * Génère toutes les entités d'un niveau depuis un fichier PPM
 * <fileName[]> : nom du fichier au format PPM décrivant le niveau
 * Retourne une structure Level
 */
Level generateLevelFromFile(const char filename[]);

/*
 * initialiseLevel
 * Initialise les attributs de la variable Level à NULL
 * <*level> : pointeur vers le Level
 */
void initialiseLevel(Level *level);

/*
 * addElementToLevel
 * ajoute des éléments selon le code ajouté
 * <code> : code de l'élément à ajouter
 * <*level> : pointeur sur le level dans lequel on ajoute
 * <x> : position en x UNITE
 * <y> : position en Y UNITE
 * Retourne 0 si l'élément n'a pas pu être alloué, 1 sinon
 */
int addEntityToLevel(EntityCode code, Level *level, float x, float y);

/*
 * removeLevelBehind
 * Enlève toutes les entités des listes du level jusqu'à xMax
 * et libère la mémoire occupée. Prend en compte la taille des entités
 * <*level> : Pointeur sur le level
 * <xMax> : Coordonnée maximum en x des entités à supprimer
 */
void removeLevelBehind(Level *level, float xMax);

/*
 * freeLevel
 * Libère la mémoire occupée par toutes les listes du niveau
 * <*level> : Pointeur sur le level
 */
void freeLevel(Level *level);

/*
 * loadBackgroundLevel
 * ajoute les entités du background au level <level>
 * N.B. La liste n'est pas triée
 * <*level> : pointeur sur le level
 */
void loadBackgroundLevel(Level *level);

#endif
