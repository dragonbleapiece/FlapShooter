/*
 * route.h
 * Déclaration des fonctions et structure des chemins des ennemis
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef ROUTE_H
#define ROUTE_H

#include <math.h>
#include <SDL/SDL.h>

typedef struct route {
  int id; /* Id de la route */
  float depX, depY, destX, destY; /* positions de départ et d'arrivée */
  Uint32 duration; /* durée du chemin */
  Uint32 startTime; /* temps du commencement du chemin */
  struct route *next; /* chemin suivant */
  struct route *first; /* premier chemin de la liste */
} Route, *RouteList;

/*
 * allocRoute
 * Alloue un chemin dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <id> : id de la route
 * <depX> : position de départ en x
 * <depY> : position de départ en y
 * <destX> : position d'arrivée en x
 * <destY> : position d'arrivée en y
 * <duration> : durée de la route
 * Retourne un pointeur sur Route
 */
Route *allocRoute(int id, float depX, float depY, float destX, float destY, int duration);

/*
 * freeRouteList
 * Libère l'espace mémoire allouée pour une liste de routes
 * <*R> : pointeur sur la liste de routes
 */
void freeRouteList(RouteList *R);

/*
 * addRouteToList
 * Ajoute une route à une liste de routes trié dans l'ordre croissant des id
 * Ne rajoute pas la route si elle a un id existant
 * <*R> : pointeur sur la liste de routes
 * <*route> : pointeur sur la route à ajouter
 */
void addRouteToList(RouteList *R, Route *route);

/*
 * getRouteByID
 * Récupère une route dans la liste de routes par son id
 * <R> : la liste de routes
 * <id> : id de la route à récupérer
 * Retourne le pointeur sur la route
 */
Route *getRouteByID(RouteList R, int id);

/*
 * allRoutesToFirstRoute
 * affecte à toutes les routes de la liste le premier élément de la liste
 * <R> : la liste de routes
 */
void allRoutesToFirstRoute(RouteList R);

/*
 * loopOnRouteByID
 * crée une boucle à partir de la route sur la route à l'id indiqué
 * <*route> : pointeur de la route que l'on veut boucler
 * <id> : indice de la route sur laquelle on veut boucler
 */
void loopOnRouteByID(Route *route, int id);

#endif
