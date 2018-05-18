#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "display.h"
#include "controls.h"

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
static unsigned int WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
static unsigned int FULLSCREEN = 0; /* 1 pour pleine écran */

float rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

void resizeViewport(Camera cam) {
  // Taille du jeu, en fonction du ratio
  int maxHeight = WINDOW_HEIGHT;
  int maxWidth = round((float) maxHeight * RATIO);
  // Pixel en excès (contours noirs)
  int extraWidth = 0, extraHeight = 0;
  // L'inverse du ratio
  float reverseRatio = 1. / ((float) RATIO);

  /* Calcul de la taille du jeu par rapport a la fenetre */
  if (maxWidth <= WINDOW_WIDTH) { // Trop large
    extraWidth = WINDOW_WIDTH - maxWidth;
  } else { // Pas assez large
    maxWidth = WINDOW_WIDTH;
    maxHeight = maxWidth * reverseRatio;
    extraHeight = WINDOW_HEIGHT - maxHeight;
  }
  glViewport(extraWidth / 2, extraHeight / 2, maxWidth, maxHeight);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(cam.xMin, cam.xMax, cam.yMax, cam.yMin);
  if (FULLSCREEN)
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE | SDL_FULLSCREEN);
  else
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
}

int main(int argc, char** argv) {

  /* Initialisation de la SDL */
  if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* On récupère la taille maximal de la fenetre de l'utilisateur*/
  const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
  int maxWindowHeight = vidinfo->current_h;
  int maxWindowWidth = vidinfo->current_w;
  /* Dernière taille de fenetre avant le pleine écran */
  int lowWindowHeight = WINDOW_HEIGHT;
  int lowWindowWidth = WINDOW_WIDTH;

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if (NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("FlapShooter", NULL);

  int loop = 1;
  // option de blending OpenGL
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Level level = generateLevelFromFile(SRC_RESOURCES_FOLDER "levelOne.ppm");
  /* Initialisation de l'affichage */
  Camera cam = initCamera(level.height);
  Controls controls = initControls();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  resizeViewport(cam);


  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);



  while (loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(cam.xMin, cam.xMax, cam.yMax, cam.yMin);
    displayLevel(level, cam);
    //translateEntity(level.player, level.speed, 0);
    translateCamera(&cam, level.speed * level.speedCoeff, 0);
    glPopMatrix();

    SDL_GL_SwapBuffers();


    executeControls(controls, level, cam);

    /* Boucle traitant les evenements */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

      switch (e.type) {


        case SDL_VIDEORESIZE: /* On redimensionne le viewport */
          WINDOW_HEIGHT = e.resize.h;
          WINDOW_WIDTH = e.resize.w;
          resizeViewport(cam);
          break;


        case SDL_KEYDOWN: /*Evénements à l'appui d'une touche*/

          switch (e.key.keysym.sym) {
            case SDLK_F12: /* Pleine écran */
              FULLSCREEN = !FULLSCREEN;
              if (FULLSCREEN) {
                lowWindowHeight = WINDOW_HEIGHT;
                lowWindowWidth = WINDOW_WIDTH;
                WINDOW_WIDTH = maxWindowWidth;
                WINDOW_HEIGHT = maxWindowHeight;
              } else {
                WINDOW_WIDTH = lowWindowWidth;
                WINDOW_HEIGHT = lowWindowHeight;
              }

              resizeViewport(cam);
              break;

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
