/*
 * display.c
 * Déclaration de la structure et des fonctions de gestion de l'affichage
 *
 * N.B. Les descriptifs des fonctions sont dans display.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "display.h"

void displayLevel(Level *lvl, Camera cam) {
  int nextSprite = 0;
  static int lastTime = 0;
  int time = SDL_GetTicks();
  // Si le temps entre 2 sprites est écoulé
  if (time - lastTime > 1000 / SPRITES_PER_SECOND) {
    nextSprite = 1; // On passe a la sprite suivante
    lastTime = time;
  }
  if (cam.xMax < lvl->width && lvl->playerStatus == 1) // si le niveau et le joueur sont en mouvement
    displayEntityBackgroundList(&(lvl->background), cam.xMin, nextSprite, lvl->speed * lvl->speedCoeff);
  else
    displayEntityBackgroundList(&(lvl->background), cam.xMin, nextSprite, 0);
  displayEntityList(&(lvl->bonus), cam.xMax, nextSprite);
  displayEntityList(&(lvl->player), cam.xMax, nextSprite);
  displayEntityList(&(lvl->obstacles), cam.xMax, nextSprite);
  executeRoutesEntityList(lvl->ennemies, cam.xMax);
  displayEntityList(&(lvl->ennemies), cam.xMax, nextSprite);
  translateEntityListBySpeed(lvl->projectiles, cam.xMax);
  removeEntityInFront(&(lvl->projectiles), cam.xMax);
  displayEntityList(&(lvl->projectiles), cam.xMax, nextSprite);
}

void displayTexturedEntity(Entity* E, float xRelative, float yRelative) {
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, *(E->texture->id));
  glPushMatrix();
  glTranslatef(E->x + xRelative, E->y + yRelative, 0);
  glScalef(E->sizeX, E->sizeY, 0);
  glBegin(GL_TRIANGLE_FAN);
  glColor4ub(255, 255, 255, 255);
  glTexCoord2f(
          (E->xTextureIndice + 0.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 1.) / E->texture->verticalDiv);
  glVertex2f(0, 1);
  glTexCoord2f(
          (E->xTextureIndice + 1.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 1.) / E->texture->verticalDiv);
  glVertex2f(1, 1);
  glTexCoord2f(
          (E->xTextureIndice + 1.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 0.) / E->texture->verticalDiv);
  glVertex2f(1, 0);
  glTexCoord2f(
          (E->xTextureIndice + 0.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 0.) / E->texture->verticalDiv);
  glVertex2f(0, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  if (SHOW_BOUNDING_BOX)
    displayBoundingBoxList(E->boundingBox, E);
  glPopMatrix();
}

void displayEntity(Entity* E, float xRelative, float yRelative) {
  if (E == NULL) return;
  glPushMatrix();
  glTranslatef(E->x + xRelative, E->y + yRelative, 0);
  glScalef(E->sizeX, E->sizeY, 0);
  glBegin(GL_TRIANGLE_FAN);
  glColor4ub(UNTEXTURED_BOX_COLOR);
  glVertex2f(0, 1);
  glVertex2f(1, 1);
  glVertex2f(1, 0);
  glVertex2f(0, 0);
  glEnd();
  if (SHOW_BOUNDING_BOX)
    displayBoundingBoxList(E->boundingBox, E);
  glPopMatrix();
}

void displayEntityList(EntityList *L, float xMax, int nextSprite) {
  EntityList cursor = *L;
  EntityList tmp;

  while (cursor != NULL && cursor->x <= xMax) {
    if (isTextured(*cursor)) {
      if (nextSprite && upXSpriteEntity(cursor) && cursor->life == 0) { // dernière sprite de destruction
        tmp = cursor->next;
        removeEntityToList(L, cursor);
        cursor = tmp;
      } else {
        displayTexturedEntity(cursor, 0., 0.);
        cursor = cursor->next;
      }
    } else {
      displayEntity(cursor, 0., 0.);
      cursor = cursor->next;
    }
  }
}

void displayEntityBackgroundList(EntityList *L, float xMin, int nextSprite, float speed) {
  EntityList cursor = *L;
  while (cursor != NULL) {
    translateEntity(cursor, cursor->speedX * speed, cursor->speedY * speed);
    if (cursor->x + cursor->sizeX <= xMin)
      cursor->x += cursor->sizeX * 2;

    if (isTextured(*cursor)) {
      if (nextSprite)
        upXSpriteEntity(cursor);
      displayTexturedEntity(cursor, 0., 0.);
    } else {
      displayEntity(cursor, 0., 0.);
    }
    cursor = cursor->next;
  }
}

void displayBoundingBox(BoundingBox *B, Entity * E) {
  if (B == NULL) return;
  BoundingShape S = B->shape;

  switch (B->type) {
    case AABB_SHAPE:
      glBegin(GL_QUADS);
      glColor4ub(BOUNDING_BOX_COLOR);
      glVertex2f(S.box.xMin, S.box.yMax);
      glVertex2f(S.box.xMax, S.box.yMax);
      glVertex2f(S.box.xMax, S.box.yMin);
      glVertex2f(S.box.xMin, S.box.yMin);
      glEnd();
      break;

    case CIRCLE_SHAPE:
      glPushMatrix();
      glTranslatef(S.circle.x, S.circle.y, 0);
      glBegin(GL_POLYGON);
      glColor4ub(BOUNDING_BOX_COLOR);
      for (int i = 0; i <= CERCLE_LIGNES; i++) {
        glVertex2f(S.circle.r * cos(2 * M_PI * i / CERCLE_LIGNES), S.circle.r * sin(2 * M_PI * i / CERCLE_LIGNES));
      }
      glEnd();
      glPopMatrix();
      break;
  }
}

void displayBoundingBoxList(BoundingBoxList L, Entity * E) {
  while (L != NULL) {
    displayBoundingBox(L, E);
    L = L->next;
  }
}

Camera initCamera(int height) {
  Camera cam;
  cam.xMin = 0;
  cam.yMin = 0;
  cam.xMax = height * RATIO;
  cam.yMax = height;

  return cam;
}

void translateCamera(Camera *cam, float x, float y) {
  cam->xMin += x;
  cam->yMin += y;
  cam->xMax += x;
  cam->yMax += y;
}

void displayEntityListOnCam(EntityList *L, Camera cam, int nextSprite) {
  EntityList cursor = *L;
  EntityList tmp;

  while (cursor != NULL) {
    if (isTextured(*cursor)) {
      if (nextSprite && upXSpriteEntity(cursor) && cursor->life == 0) { // dernière sprite de destruction
        tmp = cursor->next;
        removeEntityToList(L, cursor);
        cursor = tmp;
      } else {
        displayTexturedEntity(cursor, cam.xMin, cam.yMin);
        cursor = cursor->next;
      }
    } else {
      displayEntity(cursor, cam.xMin, cam.yMin);
      cursor = cursor->next;
    }
  }
}

void displayEntityListUILevel(UI *interface, Camera cam, int nextSprite, Level level) {
  EntityList cursor = interface->items;
  EntityList tmp;
  Texture *heart = getTextureFromList(interface->textures, SRC_HEART);
  int heartCount = 0;

  while (cursor != NULL) {
    if (isTextured(*cursor)) {
      if (nextSprite && upXSpriteEntity(cursor) && cursor->life == 0) { // dernière sprite de destruction
        tmp = cursor->next;
        removeEntityToList(&(interface->items), cursor);
        cursor = tmp;
      } else {
        if ((cursor->texture == heart && heartCount < level.player->life) || (cursor->texture != heart)) {
          displayTexturedEntity(cursor, cam.xMin, cam.yMin);
          if (cursor->texture == heart) ++heartCount;
        }
        cursor = cursor->next;
      }
    } else {
      displayEntity(cursor, cam.xMin, cam.yMin);
      cursor = cursor->next;
    }
  }
}

void displayUILevel(UI *interface, Camera cam, Level level) {
  displayEntityListUILevel(interface, cam, 0, level);
}
