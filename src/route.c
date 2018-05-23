#include "route.h"


Route *allocRoute(int id, float depX, float depY, float destX, float destY, int duration) {
  Route *tmp = (Route *)malloc(sizeof(Route));

  if (!tmp) {
    printf("Memory run out\n");
    exit(1);
  }

  tmp->id = id;
  tmp->depX = depX;
  tmp->depY = depY;
  tmp->destX = destX;
  tmp->destY = destY;
  tmp->duration = duration;
  tmp->startTime = -1;
  tmp->first = NULL;
  tmp->next = NULL;

  return tmp;
}

void freeRouteList(RouteList *R) {
  Route *temp;
  if(*R != NULL) {
    *R = (*R)->first;
    while(*R != NULL && (*R)->first != *R) {
      temp = (*R)->next;
      free(*R);
      *R = temp;
    }
    *R = NULL;
  }
}

void addRouteToList(RouteList *R, Route *route) {
  RouteList cursor = *R;
  RouteList cursorPrev = NULL;

  /* Cas simple, la liste est vide */
  if (*R == NULL) {
    *R = route;
    route->first = *R;
    return;
  }

  while (cursor != NULL) {
    /* Si l'id est plus petite, la route doit etre ajoutée avant le curseur */
    if (route->id < cursor->id) {
      if (cursorPrev) { /* S'il y a une route précédente, on ajoute route après celle-ci */
        route->next = cursorPrev->next;
        cursorPrev->next = route;
        route->first = *R;
      } else { /* Sinon, on ajoute route au début de la liste*/
        route->next = route;
        *R = route;
        allRoutesToFirstRoute(*R);
      }
      return;
    }
    /* Sinon on continue la boucle */
    cursorPrev = cursor;
    cursor = cursor->next;
  }
  /* L'entité est la plus éloigné, on la met a la fin de la liste */
  cursorPrev->next = route;
  route->first = *R;
  return;
}

void allRoutesToFirstRoute(RouteList R) {
  Route *temp = R;
  while(temp != NULL) {
    temp->first = R;
    temp = temp->next;
  }
}

Route *getRouteByID(RouteList R, int id) {
  if(R != NULL && R->id != id && R->next != R->first) {
    return getRouteByID(R->next, id);
  } else {
    return R;
  }
}

void loopOnRouteByID(Route *route, int id) {
  route->next = getRouteByID(route->first, id);
}
