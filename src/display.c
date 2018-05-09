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

void displayLevel(Level lvl, Camera cam) {
  int nextSprite = 0;
  static int lastTime = 0;
  int time = SDL_GetTicks();
  // Si le temps entre 2 sprites est écoulé
  if (time - lastTime > 1000/SPRITES_PER_SECOND) {
    nextSprite = 1; // On passe a la sprite suivante
    lastTime = time;
  }
  displayEntityList(&(lvl.player), cam.xMax, nextSprite);
  displayEntityList(&(lvl.obstacles), cam.xMax, nextSprite);
  displayEntityList(&(lvl.ennemies), cam.xMax, nextSprite);
  displayEntityList(&(lvl.bonus), cam.xMax, nextSprite);
  displayEntityList(&(lvl.projectiles), cam.xMax, nextSprite);
}

void displayTexturedEntity(Entity* E) {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, *(E->texture->id));

  glBegin(GL_QUADS);
  glTexCoord2f(
          (E->xTextureIndice + 0.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 0.) / E->texture->verticalDiv);
  glVertex2f(E->x, E->y + E->sizeY);
  glTexCoord2f(
          (E->xTextureIndice + 1.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 0.) / E->texture->verticalDiv);
  glVertex2f(E->x + E->sizeX, E->y + E->sizeY);
  glTexCoord2f(
          (E->xTextureIndice + 1.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 1.) / E->texture->verticalDiv);
  glVertex2f(E->x + E->sizeX, E->y);
  glTexCoord2f(
          (E->xTextureIndice + 0.) / E->texture->horizontalDiv,
          (E->yTextureIndice + 1.) / E->texture->verticalDiv);
  glVertex2f(E->x, E->y);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  if (SHOW_BOUNDING_BOX)
    displayBoundingBoxList(E->boundingBox, E);
}

void displayEntity(Entity* E) {
  if(E == NULL) return;
  glBegin(GL_QUADS);
  glColor4ub(UNTEXTURED_BOX_COLOR);
  glVertex2f(E->x, E->y + E->sizeY);
  glVertex2f(E->x + E->sizeX, E->y + E->sizeY);
  glVertex2f(E->x + E->sizeX, E->y);
  glVertex2f(E->x, E->y);
  glEnd();
  if (SHOW_BOUNDING_BOX)
    displayBoundingBoxList(E->boundingBox, E);
}

void displayEntityList(EntityList *L, float xMax, int nextSprite) {
  EntityList cursor = *L;
  EntityList cursorPrev = NULL;

  while (cursor != NULL && cursor->x <= xMax) {
    if (isTextured(*cursor)) {
      if (nextSprite) {
        if (upXSpriteEntity(cursor) && cursor->life == 0) {// dernière sprite de destruction
          removeEntityToList(L, cursor);
          cursor = cursorPrev;
        } else {
          displayTexturedEntity(cursor);
        }
      }
    } else {
      displayEntity(cursor);
    }
    cursorPrev = cursor;
    cursor = cursor->next;
  }
}

void displayBoundingBox(BoundingBox *B, Entity* E) {
  BoundingShape S = convertShapeToAbsolute(B->shape, B->type, E->x, E->y, E->sizeX, E->sizeY);
  if (B == NULL) return;

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

void displayBoundingBoxList(BoundingBoxList L, Entity* E) {
  while (L != NULL) {
    displayBoundingBox(L, E);
    L = L->next;
  }
}

Camera initCamera() {
  Camera cam;
  cam.xMin = 0;
  cam.yMin = 0;
  cam.xMax = WINDOW_WIDTH;
  cam.yMax = WINDOW_HEIGHT;

  return cam;
}

void translateCamera(Camera *cam, float x, float y) {
  cam->xMin += x;
  cam->yMin += y;
  cam->xMax += x;
  cam->yMax += y;
}
