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
  glPushMatrix();
  glTranslatef(cam.xMin, 0, 0);
  displayEntityList(lvl.player, cam.xMax);
  glPopMatrix();
  displayEntityList(lvl.obstacles, cam.xMax);
  displayEntityList(lvl.ennemies, cam.xMax);
  displayEntityList(lvl.projectiles, cam.xMax);
  displayEntityList(lvl.bonus, cam.xMax);
}

void displayEntity(Entity* E) {
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
  if (SHOW_BOUNDING_BOX)
    displayBoundingBoxList(E->boundingBox, E);
}

void displayEntityList(EntityList L, float maxX) {
  while (L != NULL && L->x <= maxX) {
    displayEntity(L);
    L = L->next;
  }
}

void displayBoundingBox(BoundingBox *B, Entity* E) {
  BoundingShape S = convertShapeToAbsolute(B->shape, B->type, E->x, E->y, E->sizeX, E->sizeY);
  switch (B->type) {
    case AABB_SHAPE:
      glBegin(GL_QUADS);
      glColor4ub(BOUNDING_BOX_COLOR);
      glVertex2f(S.box.xMin, S.box.xMin);
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