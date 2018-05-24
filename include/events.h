

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
 * exécute les évènements du niveau
 * <*level> : pointeur sur le niveau
 * <cam> : camera du niveau
 */
void eventsInLevel(Level *level, Camera cam);

#endif
