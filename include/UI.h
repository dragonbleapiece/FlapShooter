/*
 * ui.h
 * Déclaration de la structure et des fonctions de gestion de l'interface
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef UI_H
#define UI_H
#include <math.h>
#include "settings.h"
#include "entity.h"
#include "texture.h"
#include "level.h"

typedef struct ui {
  EntityList hearts; /* Les entités de l'interface correspondant à la vie du joueur */
  EntityList endScreens; /* Les entités de l'interface correspondant aux écrans de fin */
  TextureList textures; /* Liste des textures utilisées par l'interface */
} UI;

/*
 * initUILevel
 * Initialise toutes les valeurs de l'interface en fonction du level
 * Appelle les autres fonctions d'initialisation
 * <*interface> : Structure de l'interface à initisaliser
 * <*level> : Structure du niveau
 */
void initUILevel(UI *interface, Level level);

/*
 * initHeartsUi
 * Initialise la liste d'entités "hearts" de l'interface
 * <*interface> : Structure de l'interface
 * <size> : Nombre de coeurs maximum qui doivent être affichés
 */
void initHeartsUi(UI *interface, int size);

/*
 * initEndScreenUi
 * Initialise la liste d'entités "endScreens" de l'interface
 * <*interface> : Structure de l'interface
 * <*level> : Structure du niveau
 */
void initEndScreenUi(UI *interface, Level level);

/*
 * freeUi
 * Libère toute la mémoire occupée par les listes de l'interface
 * <*interface> : Structure de l'interface à libérer
 */
void freeUi(UI *interface);

#endif
