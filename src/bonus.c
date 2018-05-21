/*
 * bonus.c
 * Déclaration de la structure et des fonctions de gestion des bonus
 *
 * N.B. Les descriptifs des fonctions sont dans bonus.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "bonus.h"

Bonus* allocBonus(EntityCode entityCode, int startTime, int duration) {
  if (duration <= 0) return NULL;
  Bonus * tmp;
  tmp = (Bonus*) malloc(sizeof (Bonus));
  if (!tmp) {
    printf("Memory run out\n");
    exit(1);
  }
  tmp->entityCode = entityCode;
  tmp->startTime = startTime;
  tmp->duration = duration;
  tmp->next = NULL;
  return tmp;
}

int getBonusDuration(EntityCode entityCode) {
  switch (entityCode) {
    case SPEED_BONUS:
      return SPEED_BONUS_DURATION * 1000;
    case SHOT_BONUS:
      return SHOT_BONUS_DURATION * 1000;
    default:
      return 0;
  }
}

int createBonusToList(BonusList *L, EntityCode entityCode) {
  BonusList cursor = *L;
  BonusList cursorPrev = NULL;
  Bonus* tmp = NULL;

  /* Cas simple, la liste est vide */
  if (*L == NULL) {
    *L = allocBonus(entityCode, SDL_GetTicks(), getBonusDuration(entityCode));
    return 1;
  }

  while (cursor != NULL) {
    /* Si l'entityCode est plus petit, l'entité doit etre ajouté avant le curseur */
    if (entityCode < cursor->entityCode) {
      tmp = allocBonus(entityCode, SDL_GetTicks(), getBonusDuration(entityCode));
      if (cursorPrev) { /* S'il y a un bonus précédent, on ajoute tmp après celle-ci */
        tmp->next = cursorPrev->next;
        cursorPrev->next = tmp;
      } else { /* Sinon, on ajoute tmp au début de la liste*/
        tmp->next = *L;
        *L = tmp;
      }
      return 1;
    } else if (entityCode == cursor->entityCode) { /* le bonus est présent dans la liste */
      cursor->duration += getBonusDuration(entityCode); /* On allonge sa durée */
      return 0;
    }
    /* Sinon on continue la boucle */
    cursorPrev = cursor;
    cursor = cursor->next;
  }
  /* Le bonus est le plus grand, on le met a la fin de la liste */
  tmp = allocBonus(entityCode, SDL_GetTicks(), getBonusDuration(entityCode));
  cursorPrev->next = tmp;
  return 1;
}

void freeBonusList(BonusList *L) {
  if (*L != NULL) {
    freeBonusList(&(*L)->next);
    free(*L);
    /*Lui assigne NULL, prévient de bugs */
    *L = NULL;
  }
}

int isExpiredBonus(Bonus B) {
  if (SDL_GetTicks() - B.startTime > B.duration) return 1;
  else return 0;
}

int haveBonus(BonusList *L, EntityCode entityCode) {
  BonusList cursor = *L;
  BonusList cursorPrev = NULL;
  while (cursor != NULL && entityCode >= cursor->entityCode) {
    // printf("%d - ", cursor->entityCode);
    if (entityCode == cursor->entityCode) {
      if (isExpiredBonus(*cursor)) { /* Bonus expiré, on libère la mémoire */
        if (cursorPrev != NULL) cursorPrev->next = cursor->next;
        else *L = cursor->next;
        free(cursor);
        return -1;
      } else { /* Le bonus est présent et actif */
        return 1;
      }
    }
    cursorPrev = cursor;
    cursor = cursor->next;
  }
  return 0;
}

void printBonusList(BonusList L) {
  if (L == NULL)
    return;
  printf("- Bonus (%d) | duration: %d | startTime: %d \n",
          L->entityCode, L->duration, L->startTime);
  printBonusList(L->next);
}