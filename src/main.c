#include <stdlib.h>
#include <stdio.h>

#include "level.h"

float rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {

  Level level = generateLevelFromFile("ressources/levelOne.ppm");

  printEntityList(level.player);
  printEntityList(level.ennemies);
  printEntityList(level.obstacles);
  printEntityList(level.bonus);
  printEntityList(level.projectiles);

  /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }


    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Titre de la fenêtre */
    SDL_WM_SetCaption("FlapShooter", NULL);

    /* Initialisation de l'affichage */
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    SDL_GL_SwapBuffers();

    int loop = 1;

    while(loop) {

      SDL_GL_SwapBuffers();

      /* Boucle traitant les evenements */
      SDL_Event e;
      while(SDL_PollEvent(&e)) {

          /* L'utilisateur ferme la fenêtre : */
          if(e.type == SDL_QUIT) {
              loop = 0;
              break;
          }

          switch(e.type) {
            default:
              break;
          }

        }
    }

    SDL_Quit();

  return EXIT_SUCCESS;
}
