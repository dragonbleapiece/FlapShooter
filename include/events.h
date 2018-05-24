/*
 * events.h
 * Déclaration de la fonction de gestion des événements dans le niveau
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */
#ifndef EVENTS_H
#define EVENTS_H
#include <math.h>
#include "settings.h"
#include "bounding.h"
#include "display.h"
#include "collision.h"
#include "shot.h"

/*
 * eventsInLevel
 * Exécute les événements du niveau
 * <*level> : pointeur sur le niveau
 * <cam> : Caméra du niveau
 */
void eventsInLevel(Level *level, Camera cam);

#endif
