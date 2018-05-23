

#ifndef ROUTE_H
#define ROUTE_H

#include <math.h>
#include <SDL/SDL.h>

typedef struct route {
  int id;
  float depX, depY, destX, destY;
  Uint32 duration;
  Uint32 startTime;
  struct route *next;
  struct route *first;
} Route, *RouteList;

Route *allocRoute(int id, float depX, float depY, float destX, float destY, int duration);

void freeRouteList(RouteList *R);

void addRouteToList(RouteList *R, Route *route);

Route *getRouteByID(RouteList R, int id);

void allRoutesToFirstRoute(RouteList R);

void loopOnRouteByID(Route *route, int id);

#endif
