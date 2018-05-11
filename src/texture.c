/*
 * texture.c
 * Déclaration de la structure et des fonctions de gestion des textures
 *
 * N.B. Les descriptifs des fonctions sont dans texture.h
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#include "texture.h"

Texture* allocTexture(char fileName[], GLuint *id, GLint format, int verticalDiv, int horizontalDiv) {
  Texture* tmp;
  char *buffer;
  tmp = (Texture*) malloc(sizeof (Texture));
  buffer = (char *) malloc((strlen(fileName) + 1) * sizeof (char));
  if (!tmp || !buffer) {
    printf("Memory run out\n");
    exit(1);
  }
  strcpy(buffer, fileName);
  tmp->fileName = buffer;
  tmp->id = id;
  tmp->format = format;
  tmp->verticalDiv = verticalDiv;
  tmp->horizontalDiv = horizontalDiv;
  tmp->next = NULL;
  return tmp;
}

Texture* createTexture(char fileName[], int verticalDiv, int horizontalDiv) {
  /* CHARGEMENT DE LA SURFACE */
  SDL_Surface *surface = IMG_Load(fileName);
  if (!surface) {
    printf("Can not load texture %s\n", fileName);
    exit(1);
  }
  /* DEFINITION DU FORMAT */
  GLint format;
  if (surface->format->BytesPerPixel == 4) {
    if (surface->format->Rmask == 0x000000ff) format = GL_RGBA;
    else format = GL_BGRA;
  } else if (surface->format->BytesPerPixel == 3) {
    if (surface->format->Rmask == 0x000000ff) format = GL_RGB;
    else format = GL_BGR;
  } else {
    printf("Can not load texture %s\n", fileName);
    exit(1);
  }

  /* ENVOI DES DONNEES A LA CARTE GRAPHIQUE */
  GLuint *id;
  id = (GLuint*) malloc(sizeof (id));
  if (!id) {
    printf("Memory run out\n");
    exit(1);
  }
  glGenTextures(1, id);
  glBindTexture(GL_TEXTURE_2D, *id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(
          GL_TEXTURE_2D,
          0,
          format,
          surface->w,
          surface->h,
          0,
          format,
          GL_UNSIGNED_BYTE,
          surface->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* LIBERER LA SURFACE */
  SDL_FreeSurface(surface);

  /* ALLOCATION DE LA TEXTURE */
  return allocTexture(fileName, id, format, verticalDiv, horizontalDiv);
}

Texture* createTextureToList(TextureList *L, char fileName[], int verticalDiv, int horizontalDiv) {
  int resStrCmp;

  TextureList cursor = *L;
  TextureList cursorPrec = NULL;

  /* Cas simple, la liste est vide */
  if (*L == NULL) {
    *L = createTexture(fileName, verticalDiv, horizontalDiv);
    return *L;
  }

  while (cursor != NULL) {
    resStrCmp = strcmp(fileName, cursor->fileName);

    if (resStrCmp < 0) { /* fileName est inférieur lexicographiquement au mot du curseur, donc il n'est pas dans la liste et il doit etre creer avant celui-ci */
      Texture *newTexture = createTexture(fileName, verticalDiv, horizontalDiv);
      if (cursorPrec) { /* S'il y a une texture précédente, on creer la cellule après celle-ci */
        newTexture->next = cursorPrec->next;
        cursorPrec->next = newTexture;
      } else { /* Sinon, on creer une cellule au début */
        newTexture->next = *L;
        *L = newTexture;
      }
      return newTexture;
    } else if (resStrCmp == 0) { /* fileName est présent dans la liste, on renvoie la texture */
      return cursor;
    }
    cursorPrec = cursor;
    cursor = cursor->next;
  }
  /* Le mot n'est pas dans la liste et doit être mis a la fin */
  Texture *newTexture = createTexture(fileName, verticalDiv, horizontalDiv);
  cursorPrec->next = newTexture;
  return newTexture;
}

void freeTextureList(TextureList *L) {
  if (*L != NULL) {
    freeTextureList(&(*L)->next);
    glDeleteTextures(1, (*L)->id); /* Libération des données GPU */
    free(*L);
    /*Lui assigne NULL, prévient de bugs */
    *L = NULL;
  }
}

Texture* getTextureFromList(TextureList L, char fileName[]) {
  Texture *cursor = L;
  int resStrCmp;
  if (cursor == NULL) /* Liste vide */
    return NULL;

  while (cursor != NULL) {
    resStrCmp = strcmp(fileName, cursor->fileName);
    /* fileName est inférieur lexicographiquement au mot du curseur, donc il n'est pas dans la liste */
    if (resStrCmp < 0)
      return NULL;
    /* fileName est présent dans la liste, on renvoie sa texture */
    if (resStrCmp == 0)
      return cursor;
    cursor = cursor->next;
  }
  /* Si rien n'a était trouvé dans la liste */
  return NULL;
}