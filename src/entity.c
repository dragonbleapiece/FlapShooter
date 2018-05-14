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

Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, Texture *texture, BoundingBoxList boundingBox) {
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
  tmp->shotFrequency = 0;
  tmp->maxLife = maxLife;
  tmp->life = maxLife;
  tmp->attack = attack;
  tmp->texture = texture;
  tmp->xTextureIndice = 0;
  tmp->yTextureIndice = 0;
  tmp->boundingBox = boundingBox;
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
          L->x / UNITE, L->y / UNITE, L->sizeX, L->sizeY, L->life, L->maxLife, L->attack);
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
    /*On libère les bounding box puis l'entité*/
    freeBoundingBoxList(&(E->boundingBox));
    free(E);
    return 1;
  }

  return 0;
}

void removeEntityBehind(EntityList *L, float xMax) {
  while (*L != NULL && (*L)->x <= xMax + (*L)->sizeX) {
    free(*L);
    *L = (*L)->next;
  }
}

void freeEntityList(EntityList *L) {
  if (*L != NULL) {
    freeEntityList(&(*L)->next);
    /*On libère les bounding box puis l'entité*/
    freeBoundingBoxList(&((*L)->boundingBox));
    free(*L);
    /*Lui assigne NULL, prévient de bugs */
    *L = NULL;
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
