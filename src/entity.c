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

Entity* allocEntity(float x, float y, float sizeX, float sizeY, int maxLife, int attack, GLuint textureID, BoundingBoxList boundingBox) {
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
  tmp->maxLife = maxLife;
  tmp->life = maxLife;
  tmp->attack = attack;
  tmp->textureID = textureID;
  tmp->boundingBox = boundingBox;
  tmp->next = NULL;
  return tmp;
}

/*
 * addEntityToList
 * Ajoute l'entité <*E> à la liste <*L> triée par position x
 * <*L> : Pointeur de la liste triée d'entité
 * <*E> : Entité a ajouter, supposé dans aucune liste
 */
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

void printEntityList(EntityList L) {
  if (L == NULL)
    return;
  printf("- Entité (%f;%f) | taille: %fx%f | vie: %d/%d | Attaque: %d | textureId: %d\n",
          L->x, L->y, L->sizeX, L->sizeY, L->life, L->maxLife, L->attack, (int) L->textureID);
  printEntityList(L->next);
}

/*
 * removeEntityToList
 * Enleve l'entité <E> de la liste <*L> et libére la mémoire occupée
 * <*L> : Pointeur de la liste triée d'entité
 * <E> : Entité a supprimer, supposé dans la liste
 * retourne 1 si l'entité a été enlevée, 0 sinon
*/
int removeEntityToList(EntityList *L, EntityList E) {
  EntityList cursor = *L;
  EntityList cursorPrev = NULL;

  while(cursor != NULL && cursor != E) {
    cursorPrev = cursor;
    cursor = cursor->next;
  }

  /*Si une fois sorti de la boucle, le cursor est à E*/
  if(cursor == E) {
    /*Si le cursorPrev est à NULL alors, *E est en tête de liste*/
    if(cursorPrev != NULL) cursorPrev->next = E->next;
    else *L = E->next;
    /*On libère l'entité*/
    free(E);
    return 1;
  }

  return 0;
}

/*
 * freeEntityList
 * Libére la mémoire occupée par toutes les entités de la liste <*L>
 * <*L> : Pointeur de la liste triée d'entité
*/

void freeEntityList(EntityList *L) {
  if(*L != NULL) {
    freeEntityList(&(*L)->next);
    free(*L);
    /*Lui assigne NULL, prévient de bugs*/
    *L = NULL;
  }
}

/*
 * isColliding
 * Test si l'entité <E1> et en collision avec l'entité <E2>
 * Retourne 1 si collision, 0 sinon
*/

/*Fait Seulement Pour le carré !!!!*/
int isColliding(Entity E1, Entity E2) {
  BoundingBoxList B1 = E1.boundingBox, B2 = E2.boundingBox;
  int r = 0;
  while(B1 != NULL && !r) {
    while(B2 != NULL && !r) {
      r = !((B2->xMin + E2.x >= B1.xMax + E1.x)  // trop à droite
        	|| (B2.xMax + E2.x <= B1.xMin + E1.x) // trop à gauche
        	|| (B2.yMin + E2.y >= B1.yMax + E1.y) // trop en bas
        	|| (box2.yMax + E2.y <= box1.yMin + E1.y));  // trop en haut

      B2 = B2->next;
    }

    B1 = B1->next;
  }

  return r;
}

/*
 * isCollidingWith
 * Test si l'entité <E> et en collision avec l'une des entités de la liste <L>
 * <maxX> : Coordonnée maximum en x des entités a tester
 * Retourne un pointeur sur la première entité qui est en collision, NULL sinon

Entity* isCollidingWith(Entity E, EntityList L, float maxX);

 */
