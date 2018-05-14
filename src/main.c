#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "controls.h"

float rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {

  /* Initialisation de la SDL */
  if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if (NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("FlapShooter", NULL);

  int loop = 1;
  Camera cam = initCamera();
  Controls controls = initControls();

  /* Initialisation de l'affichage */

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glViewport(cam.xMin, cam.yMin, cam.xMax, cam.yMax);
  gluOrtho2D(cam.xMin, cam.xMax, cam.yMax, cam.yMin);

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // option de blending OpenGL
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Level level = generateLevelFromFile(SRC_RESOURCES_FOLDER "levelOne.ppm");

  while (loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(-cam.xMin, 0, 0);
    displayLevel(level, cam);
    //translateEntity(level.player, LEVEL_SPEED, 0);
    translateCamera(&cam, LEVEL_SPEED, 0);
    glPopMatrix();

    SDL_GL_SwapBuffers();


    executeControls(controls, level, cam);

    /* Boucle traitant les evenements */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

      switch (e.type) {

        case SDL_KEYDOWN: /*Evénements à l'appui d'une touche*/

          switch (e.key.keysym.sym) {
            case SDLK_SPACE:
              controls.space = 1;
              break;

            case SDLK_LEFT:
              controls.left = 1;
              break;

            case SDLK_RIGHT:
              controls.right = 1;
              break;

            case SDLK_UP:
              controls.up = 1;
              break;

            case SDLK_DOWN:
              controls.down = 1;
              break;

            default:
              break;
          }

          break;

        case SDL_KEYUP: /*Evénements au relachement d'une touche*/

          switch (e.key.keysym.sym) {
            case SDLK_SPACE:
              controls.space = 0;
              break;

            case SDLK_LEFT:
              controls.left = 0;
              break;

            case SDLK_RIGHT:
              controls.right = 0;
              break;

            case SDLK_UP:
              controls.up = 0;
              break;

            case SDLK_DOWN:
              controls.down = 0;
              break;

            default:
              break;
          }

          break;

          /* L'utilisateur ferme la fenêtre : */
        case SDL_QUIT:
          loop = 0;
          break;

        default:
          break;
      }

    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if (elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }

  }

  SDL_Quit();
  freeLevel(&level);

  return EXIT_SUCCESS;
}
