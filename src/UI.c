/*
 * ui.c
 * Déclaration de la structure et des fonctions de gestion de l'interface
 *
 * N.B. Les descriptifs des fonctions sont dans ui.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "UI.h"

void initUILevel(UI *interface, Level level) {
  interface->hearts = NULL;
  interface->endScreens = NULL;
  interface->textures = NULL;
  initHeartsUi(interface, level.player->maxLife);
  initEndScreenUi(interface, level);
}

void initHeartsUi(UI *interface, int number) {
  Entity *item;
  float size = 16. / UNITE;
  float margin = 0.1;
  int i;
  Texture *t = createTextureToList(&(interface->textures), SRC_HEART, 1, 1);
  for (i = 1; i <= number; ++i) {
    item = allocEntity((margin + size) * i, margin, size, size, -1, 0., t, NULL, VOID_CODE);
    addEntityToList(&(interface->hearts), item);
  }
}

void initEndScreenUi(UI *interface, Level level) {
  Entity *item;
  Texture *t;
  t = createTextureToList(&(interface->textures), SRC_WIN_UI, 1, 1);
  item = allocEntity(0, 0, level.height * RATIO, level.height, -1, 0., t, NULL, VOID_CODE);
  addEntityToList(&(interface->endScreens), item);
  t = createTextureToList(&(interface->textures), SRC_LOSE_UI, 1, 1);
  item = allocEntity(0, 0, level.height * RATIO, level.height, -1, 0., t, NULL, VOID_CODE);
  addEntityToList(&(interface->endScreens), item);
}

void freeUi(UI *interface) {
  freeEntityList(&interface->hearts);
  freeEntityList(&interface->endScreens);
  freeTextureList(&interface->textures);
}