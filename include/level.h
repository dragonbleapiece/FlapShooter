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
#include "settings.h"
#include "entity.h"

typedef struct level {
  EntityList player; /* Liste de l'entité joueur */
  EntityList obstacles; /* Liste triée d'entité obstacles */
  EntityList ennemies; /* Liste triée d'entité ennemis */
  EntityList bonus; /* Liste triée d'entité bonus */
  EntityList projectiles; /* Liste triée d'entité projectiles */
  EntityList background; /* liste NON triée des éléments du background */
  TextureList textures; /* Liste triée contenant toute les textures utilisées */
  int height, width;
  float speed;
  float speedCoeff;
} Level;

/*
 * generateLevelFromFile
 * Génére toutes les entités d'un niveau depuis un fichier PPM
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
 * Retourne false si l'élément n'a pas pu être alloué, true sinon
 */
int addEntityToLevel(EntityCode code, Level *level, float x, float y);

/*
 * freeLevel
 * Libère la mémoire occupée par toutes les listes du niveau
 * <*L> : Pointeur de la liste triée d'entités
 */
void freeLevel(Level *L);

/*
 * loadBackgroundLevel
 * ajoute les entités du background au level <level>
 * N.B. La liste n'est pas triée
 * <*level> : pointeur sur le level
 */
void loadBackgroundLevel(Level *level);

#endif
