/*
 * bonus.h
 * Déclaration de la structure et des fonctions de gestion des bonus
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef BONUS_H
#define BONUS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "settings.h"
#include "tools.h"
#include "entity.h"

typedef struct bonus {
  EntityCode entityCode; /* Code de l'entité bonus, sert d'identifiant */
  int startTime; /* Début de l'effet du bonus */
  int duration; /* Durée de l'effet du bonus en ms */
  struct bonus* next; /* Pointeur sur le bonus suivant dans la liste */
} Bonus, *BonusList;

/*
 * allocBonus
 * Alloue un bonus dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <entityCode> : Code de l'entité bonus (identifiant)
 * <startTime> : Début de l'effet du bonus
 * <duration> : Durée de l'effet du bonus
 * Retourne un pointeur sur la texture
 */
Bonus* allocBonus(EntityCode entityCode, int startTime, int duration);

/*
 * getBonusDuration
 * Renvoie la durée normal du bonus <entityCode>, 0 si introuvable
 */
int getBonusDuration(EntityCode entityCode);

/*
 * createBonusToList
 * Créer et ajoute un bonus à la liste <*L> triée par ordre croissant d'identifiant
 * Si le bonus est deja présent, on met a jours sa durée
 * <*L> : Pointeur de la liste triée de bonus
 * <entityCode> : Code de l'entité
 * Retourne 1 si le bonus a été créé, 0 si il a été mis a jours
 */
int createBonusToList(BonusList *L, EntityCode entityCode);

/*
 * freeBonusList
 * Libére la mémoire occupée par tous les bonus de la liste <*L>
 * <*L> : Pointeur de la liste triée de bonus
 */
void freeBonusList(BonusList *L);

/*
 * isExpiredBonus
 * Test si le bonus <B> a expiré
 * Retourne 1 si le bonus a expiré, 0 sinon
 */
int isExpiredBonus(Bonus B);

/*
 * haveBonus
 * Test si la liste <*L> a le bonus <entityCode>
 * Si le bonus a expiré, la mémoire est libéré et la fonction retourne 0
 * Retourne 1 si le bonus est présent dans la liste, 0 sinon
 */
int haveBonus(BonusList *L, EntityCode entityCode);


#endif
