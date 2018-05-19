/*
 * texture.h
 * Déclaration de la structure et des fonctions de gestion des textures
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "settings.h"
#include "tools.h"

typedef struct texture {
  char *fileName; /* Chaine de caractère représentant le nom et l'extention de l'image, sert d'identifiant */
  GLuint *id; /* Identifiant GLuint de la texture */
  GLint format; /* Format de l'image (GL_RGB ou GL_RGBA), déterminé automatiquement en fonction de l'extention de l'image */
  int verticalDiv; /* Division vertical de l'image pour les sprites, 1 si aucune */
  int horizontalDiv; /* Division horizontal de l'image pour les "sprites", 1 si aucune */
  struct texture* next; /* Pointeur sur la texture suivante dans la liste */
} Texture, *TextureList;

/*
 * allocTexture
 * Alloue une texture dans l'espace mémoire et initialise ses paramétres
 * Quitte le programme en cas d'erreur d'allocation
 * <fileName[]> : Nom et extention de l'image (identifiant)
 * <*id> : Identifiant GLuint de la texture
 * <format> : Format de l'image (GL_RGB ou GL_RGBA)
 * <verticalDiv> : Division vertical de l'image
 * <horizontalDiv> : Division horizontal de l'image 
 * Retourne un pointeur sur la texture
 */
Texture* allocTexture(char fileName[], GLuint *id, GLint format, int verticalDiv, int horizontalDiv);

/*
 * createTexture
 * Charge une texture et l'alloue dans l'espace mémoire :
 *    - Charge l'image
 *    - Détermine son format en fonction de son extention
 *    - Créer l'objet texture en OpenGL et envoie les données au GPU
 *    - Libère les données CPU
 * Quitte le programme en cas d'erreur
 * <fileName[]> : Nom et extention de l'image
 * <verticalDiv> : Division vertical de l'image
 * <horizontalDiv> : Division horizontal de l'image 
 * Retourne un pointeur sur la texture alloué avec allocTexture
 */
Texture* createTexture(char fileName[], int verticalDiv, int horizontalDiv);

/*
 * createTextureToList
 * Créer et ajoute une texture à la liste <*L> triée par ordre alphabétique de fileName
 * L'ajout se fait uniquement si la texture <fileName> n'est pas dans la liste,
 * Sinon la fonction renvoie la texture existante
 * <*L> : Pointeur de la liste triée de texture
 * <fileName[]> : Nom et extention de l'image
 * <verticalDiv> : Division vertical de l'image
 * <horizontalDiv> : Division horizontal de l'image
 * Returne un pointeur sur la texture ajouté ou celle dejà présente
 */
Texture* createTextureToList(TextureList *L, char fileName[], int verticalDiv, int horizontalDiv);

/*
 * freeTextureList
 * Libére la mémoire occupée (OpenGL et structure) par toutes les textures de la liste <*L>
 * <*L> : Pointeur de la liste triée de textures
 */
void freeTextureList(TextureList *L);

/*
 * getTextureFromList
 * Cherche et retourne la texture de la liste <*L> correspondant à <fileName>
 * <L> : Liste triée de texture
 * <fileName[]> : Nom et extention de l'image
 * Returne un pointeur sur la texture, NULL si inexistante
 */
Texture* getTextureFromList(TextureList L, char fileName[]);


#endif
