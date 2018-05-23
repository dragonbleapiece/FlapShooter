/*
 * entity.c
 * Déclaration de la structure et des fonctions de gestion des entités (vaiseaux, obstacles, bonus etc...)
 *
 * N.B. Les descriptifs des fonctions sont dans entity.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "entity.h"

Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, Texture *texture, BoundingBoxList boundingBox, EntityCode entityCode) {
  Entity* tmp;
  tmp = (Entity*) malloc(sizeof (Entity));
  if (!tmp) {
    printf("Memory run out\n");
    exit(1);
  }
  tmp->x = x;
  tmp->y = y;
  tmp->sizeX = sizeX;
  tmp->sizeY = sizeY;
  tmp->speedX = 0;
  tmp->speedY = 0;
  tmp->shotX = 0;
  tmp->shotY = 0;
  tmp->lastShot = 0;
  tmp->shotFrequency = 0;
  tmp->maxLife = maxLife;
  tmp->life = maxLife;
  tmp->attack = attack;
  tmp->texture = texture;
  tmp->xTextureIndice = 0;
  tmp->yTextureIndice = 0;
  tmp->entityCode = entityCode;
  tmp->boundingBox = boundingBox;
  tmp->routes = NULL;
  tmp->next = NULL;
  return tmp;
}

void addEntityToList(EntityList *L, Entity *E) {
  EntityList cursor = *L;
  EntityList cursorPrev = NULL;

  /* Cas simple, la liste est vide */
  if (*L == NULL) {
    *L = E;
    return;
  }

  while (cursor != NULL) {
    /* Si la position est plus petite, l'entité doit etre ajouté avant le curseur */
    if (E->x < cursor->x) {
      if (cursorPrev) { /* S'il y a une entité précédente, on ajoute E après celle-ci */
        E->next = cursorPrev->next;
        cursorPrev->next = E;
      } else { /* Sinon, on ajoute E au début de la liste*/
        E->next = *L;
        *L = E;
      }
      return;
    }
    /* Sinon on continue la boucle */
    cursorPrev = cursor;
    cursor = cursor->next;
  }
  /* L'entité est la plus éloigné, on la met a la fin de la liste */
  cursorPrev->next = E;
  return;
}

void addEntityToUnsortedList(EntityList *L, Entity *E) {
  EntityList cursor = *L;
  /* Cas simple, la liste est vide */
  if (*L == NULL) {
    *L = E;
    return;
  }
  while (cursor->next != NULL) {
    cursor = cursor->next;
  }
  cursor->next = E;
}

void printEntityList(EntityList L) {
  if (L == NULL)
    return;
  printf("- Entité (%f;%f) | taille: %fx%f | vie: %d/%d | Attaque: %d \n",
          L->x, L->y, L->sizeX, L->sizeY, L->life, L->maxLife, L->attack);
  printEntityList(L->next);
}

int removeEntityToList(EntityList *L, EntityList E) {
  EntityList cursor = *L;
  EntityList cursorPrev = NULL;

  while (cursor != NULL && cursor != E) {
    cursorPrev = cursor;
    cursor = cursor->next;
  }

  /*Si une fois sorti de la boucle, le cursor est à E*/
  if (cursor == E) {
    /*Si le cursorPrev est à NULL alors, *E est en tête de liste*/
    if (cursorPrev != NULL) cursorPrev->next = E->next;
    else *L = E->next;
    /* On libère les bounding box puis l'entité */
    freeBoundingBoxList(&(E->boundingBox));
    free(E);
    return 1;
  }

  return 0;
}

void removeEntityBehind(EntityList *L, float xMax) {
  if (*L != NULL && (*L)->x + (*L)->sizeX <= xMax) {
    Entity* tmp = *L;
    *L = (*L)->next;
    removeEntityBehind(L, xMax);
    freeEntity(tmp);
  }
}

void removeEntityInFront(EntityList *L, float xMax) {
  if (*L == NULL) return;
  EntityList cursor = *L;
  EntityList cursorPrev = NULL;
  while (cursor != NULL && cursor->x <= xMax) {
    cursorPrev = cursor;
    cursor = cursor->next;
  }
  if (cursor != NULL) {
    freeEntityList(&cursor);
    if (cursorPrev != NULL) cursorPrev->next = NULL;
    else *L = NULL;
  }
}

void freeEntity(Entity *E) {
  if (E != NULL) {
    /*On libère les bounding box puis l'entité*/
    freeBoundingBoxList(&(E->boundingBox));
    freeRouteList(&(E->routes));
    free(E);
  }
}

void freeEntityList(EntityList *L) {
  if (*L != NULL) {
    freeEntityList(&((*L)->next));
    freeEntity(*L);
  }
}

int isTextured(Entity E) {
  return (E.texture != NULL);
}

int upXSpriteEntity(Entity *E) {
  E->xTextureIndice++;
  if (E->xTextureIndice >= E->texture->horizontalDiv) {
    E->xTextureIndice = 0;
    E->yTextureIndice = 0;
    return 1;
  }
  return 0;
}

int setSpriteEntity(Entity *E, int x, int y) {
  if (x >= E->texture->horizontalDiv || y >= E->texture->verticalDiv)
    return 0;
  E->xTextureIndice = x;
  E->yTextureIndice = y;
  return 1;
}

void translateEntity(Entity *E, float x, float y) {
  E->x += x;
  E->y += y;
}

void translateEntityList(EntityList L, float x, float y, float xMax) {
  while (L != NULL && L->x <= xMax) {
    translateEntity(L, x, y);
    L = L->next;
  }
}

void translateEntityBySpeed(Entity *E) {
  if (E->life == 0) return;
  translateEntity(E, (float) convert_speed(E->speedX), (float) convert_speed(E->speedY));
}

void translateEntityListBySpeed(EntityList L, float xMax) {
  while (L != NULL && L->x <= xMax) {
    translateEntityBySpeed(L);
    L = L->next;
  }
}

void attacks(Entity *E1, Entity *E2) {
  if (E2->maxLife != -1) getDamaged(E2, E1->attack);
}

void attacksBetween(Entity *E1, Entity *E2) {
  attacks(E1, E2);
  attacks(E2, E1);
}

void getDamaged(Entity *E, int damage) {
  if (damage == -1)
    E->life = 0;
  else
    E->life = clamp_start(E->life - damage, 0.);
  if (E->life == 0) {
    setSpriteEntity(E, 0, E->texture->verticalDiv - 1);
    freeBoundingBoxList(&(E->boundingBox));
  }
}

void getHealed(Entity *E, int heal) {
  E->life = clamp_end(E->life + heal, E->maxLife);
}


void executeRoutesEntityList(EntityList L, float xMax) {
  while(L != NULL && L->x < xMax) {
    executeRouteList(L);
    L = L->next;
  }
}

void executeRouteList(Entity *E) {

  if(E->routes != NULL) {
    if(E->routes == E->routes->first && E->routes->startTime == -1) E->routes->startTime = SDL_GetTicks();
    if(!executeFirstRoute(E) && E->routes->next != NULL) {
        E->routes->startTime = -1;
        E->routes = E->routes->next;
        E->routes->startTime = SDL_GetTicks();
      }
  }

}

int executeFirstRoute(Entity *E) {

  if(E->routes == NULL) return -1;

  float speedX, speedY;
  speedX = (E->routes->destX - E->routes->depX) / E->routes->duration;
  speedY = (E->routes->destY - E->routes->depY) / E->routes->duration;

  if(E->routes->startTime + E->routes->duration * 1000 > SDL_GetTicks()) {
    if (E->y < E->routes->destY) E->speedY = clamp_end(E->y + speedY, E->routes->destY) - E->y;
    else if (E->y > E->routes->destY) E->speedY = clamp_start(E->y + speedY, E->routes->destY) - E->y;

    if (E->x < E->routes->destX) E->speedX = clamp_end(E->x + speedX, E->routes->destX) - E->x;
    else if (E->x > E->routes->destX) E->speedX = clamp_start(E->x + speedX, E->routes->destX) - E->x;

    translateEntityBySpeed(E);

    return 1;

  }

  return 0;
}

void initRouteListForEnnemyOne(Entity *E) {
  int id = 0;
  Route *temp = allocRoute(id++, E->x, E->y, E->x + ENNEMYONE_MOVE_X, E->y + ENNEMYONE_MOVE_Y, ENNEMYONE_MOVE_DURATION / 2.);
  addRouteToList(&(E->routes), temp);
  temp = allocRoute(id++, E->x + ENNEMYONE_MOVE_X, E->y + ENNEMYONE_MOVE_Y, E->x - ENNEMYONE_MOVE_X, E->y - ENNEMYONE_MOVE_Y, ENNEMYONE_MOVE_DURATION);
  addRouteToList(&(E->routes), temp);
  temp = allocRoute(id++, E->x - ENNEMYONE_MOVE_X, E->y - ENNEMYONE_MOVE_Y, E->x + ENNEMYONE_MOVE_X, E->y + ENNEMYONE_MOVE_Y, ENNEMYONE_MOVE_DURATION);
  addRouteToList(&(E->routes), temp);
  loopOnRouteByID(temp, 1);
}
