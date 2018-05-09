/*
 * bounding.c
 * Déclaration de la structure et des fonctions de gestion des bounding box et de leurs forme
 *
 * N.B. Les descriptifs des fonctions sont dans bounding.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "bounding.h"

BoundingBox* allocBoundingBox(BoundingShape shape, ShapeType type) {
  BoundingBox* tmp;
  tmp = (BoundingBox*) malloc(sizeof (BoundingBox));
  if (!tmp) {
    printf("Memory run out\n");
    exit(1);
  }
  tmp->shape = shape;
  tmp->type = type;
  tmp->next = NULL;
  return tmp;
}

void addBoundingBoxToList(BoundingBoxList *L, BoundingBox *B) {
  B->next = *L;
  *L = B;
}

BoundingBox* createAABBBoundingBox(float w, float h) {
  BoundingShape shape;
  shape.box.xMin = 0.5 - w / 2;
  shape.box.xMax = 0.5 + w / 2;
  shape.box.yMin = 0.5 - h / 2;
  shape.box.yMax = 0.5 + h / 2;
  return allocBoundingBox(shape, AABB_SHAPE);
}

BoundingBox* createSquareBoundingBox(float size) {
  return createAABBBoundingBox(size, size);
}

BoundingBox* createCircleBoundingBox(float radius) {
  BoundingShape shape;
  shape.circle.x = 0.5;
  shape.circle.y = 0.5;
  shape.circle.r = radius;
  return allocBoundingBox(shape, CIRCLE_SHAPE);
}

BoundingBox* createCapsuleBoundingBox(float w, float h) {
  BoundingBoxList list = NULL;
  BoundingShape s1, s2;
  s1.circle.x = 0.5 - (w - h) / 2;
  s1.circle.y = 0.5;
  s1.circle.r = h / 2;
  s2.circle.x = 0.5 + (w - h) / 2;
  s2.circle.y = 0.5;
  s2.circle.r = h / 2;
  addBoundingBoxToList(&list, allocBoundingBox(s1, CIRCLE_SHAPE));
  addBoundingBoxToList(&list, allocBoundingBox(s2, CIRCLE_SHAPE));
  addBoundingBoxToList(&list, createAABBBoundingBox(w - h, h));
  return list;
}

BoundingShape convertShapeToAbsolute(BoundingShape shape, ShapeType type, float x, float y, float sizeX, float sizeY) {
  BoundingShape res;
  switch (type) {
    case AABB_SHAPE:
      res.box = convertAABBtoAbsolute(shape.box, x, y, sizeX, sizeY);
      break;
    case CIRCLE_SHAPE:
      res.circle = convertCircleToAbsolute(shape.circle, x, y, sizeX, sizeY);
      break;
    default:
      res = shape;
  }
  return res;
}

AABB convertAABBtoAbsolute(AABB box, float x, float y, float sizeX, float sizeY) {
  AABB res;
  res.xMin = box.xMin * sizeX + x;
  res.xMax = box.xMax * sizeX + x;
  res.yMin = box.yMin * sizeY + y;
  res.yMax = box.yMax * sizeY + y;
  return res;
}

Circle convertCircleToAbsolute(Circle circle, float x, float y, float sizeX, float sizeY) {
  Circle res;
  res.x = circle.x * sizeX + x;
  res.y = circle.y * sizeY + y;
  res.r = circle.r * sizeX;
  return res;
}

AABB convertCircleToAABB(Circle circle) {
  AABB res;
  res.xMin = circle.x - circle.r;
  res.xMax = circle.x + circle.r;
  res.yMin = circle.y - circle.r;
  res.yMax = circle.y + circle.r;
  return res;
}

int isCollidingShape(BoundingShape S1, ShapeType type1, BoundingShape S2, ShapeType type2) {
  switch (type1) {
    case AABB_SHAPE:
      switch (type2) {
        case AABB_SHAPE:
          return isCollidingAABB(S1.box, S2.box);
        case CIRCLE_SHAPE:
          return isCollidingAABBandCircle(S1.box, S2.circle);
      }
    case CIRCLE_SHAPE:
      switch (type2) {
        case AABB_SHAPE:
          return isCollidingAABBandCircle(S2.box, S1.circle);
        case CIRCLE_SHAPE:
          return isCollidingCircle(S1.circle, S2.circle);
      }
  }
  return 0;
}

int isCollidingAABB(AABB B1, AABB B2) {
  return !((B2.xMin >= B1.xMax) // trop à droite
          || (B2.xMax <= B1.xMin) // trop à gauche
          || (B2.yMin >= B1.yMax) // trop en bas
          || (B2.yMax <= B1.yMin)); // trop en haut
}

int isCollidingCircle(Circle C1, Circle C2) {
  int d2 = (C1.x - C2.x)*(C1.x - C2.x) + (C1.y - C2.y)*(C1.y - C2.y);
  return !(d2 > (C1.r + C2.r)*(C1.r + C2.r));
}

int isCollidingAABBandCircle(AABB B, Circle C) {
  /* On test s'il y a une collision entre B et la représentation AABB de C */
  if (!isCollidingAABB(B, convertCircleToAABB(C)))
    return 0;

  /* On test si un des sommets de B est dans C */
  if (isCollidingPointAndCircle(B.xMin, B.yMin, C)
          || isCollidingPointAndCircle(B.xMin, B.yMax, C)
          || isCollidingPointAndCircle(B.xMax, B.yMax, C)
          || isCollidingPointAndCircle(B.xMax, B.yMin, C))
    return 1;

  /* On test si le centre du cercle est dans le AABB */
  if (isCollidingPointAndAABB(C.x, C.y, B))
    return 1; // troisieme test

  /* On test les projections du centre du cercle sur les segments de AABB */
  int projvertical = projectionOnSegment(C.x, C.y, B.xMin, B.yMin, B.xMin, B.yMax);
  int projhorizontal = projectionOnSegment(C.x, C.y, B.xMin, B.yMin, B.xMax, B.yMin);
  return (projvertical || projhorizontal);
}

int isCollidingPointAndCircle(float x, float y, Circle C) {
  int d2 = (x - C.x)*(x - C.x) + (y - C.y)*(y - C.y);
  return !(d2 > C.r * C.r);
}

int isCollidingPointAndAABB(float x, float y, AABB box) {
  return (x >= box.xMin
          && x < box.xMax
          && y >= box.yMin
          && y < box.yMax);
}

int projectionOnSegment(int Cx, int Cy, int Ax, int Ay, int Bx, int By) {
  int ACx = Cx - Ax;
  int ACy = Cy - Ay;
  int ABx = Bx - Ax;
  int ABy = By - Ay;
  int BCx = Cx - Bx;
  int BCy = Cy - By;
  int s1 = (ACx * ABx) + (ACy * ABy);
  int s2 = (BCx * ABx) + (BCy * ABy);
  return !(s1 * s2 > 0);
}
