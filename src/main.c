#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "display.h"
#include "controls.h"
#include "events.h"
#include "UI.h"

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
static unsigned int WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
static unsigned int FULLSCREEN = 0; /* 1 pour plein écran */

void resizeViewport(Camera cam) {
  // Taille du jeu, en fonction du ratio
  int maxHeight = WINDOW_HEIGHT;
  int maxWidth = round((float) maxHeight * RATIO);
  // Pixel en excès (contours noirs)
  int extraWidth = 0, extraHeight = 0;
  // L'inverse du ratio
  float reverseRatio = 1. / ((float) RATIO);

  /* Calcul de la taille du jeu par rapport à la fenêtre */
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

  /* On récupère la taille maximale de la fenêtre de l'utilisateur */
  const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
  int maxWindowHeight = vidinfo->current_h;
  int maxWindowWidth = vidinfo->current_w;
  /* Dernière taille de fenêtre avant le plein écran */
  int lowWindowHeight = WINDOW_HEIGHT;
  int lowWindowWidth = WINDOW_WIDTH;
  /* Initialisation du rand (seed) */
  srand(time(NULL));

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if (NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("FlapShooter", NULL);

  int loop = 1;
  char levelName[] = SRC_RESOURCES_FOLDER "levelOne.ppm";
  /* Options de blending OpenGL */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Level level = generateLevelFromFile(levelName);
  /* Initialisation de l'affichage */
  Camera cam = initCamera(level.height);
  Controls controls = initControls();

  UI interface;
  initUILevel(&interface, level);

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
    displayLevel(&level, cam);

    if (level.player == NULL) // le joueur est mort
      level.playerStatus = 0;
    else if (level.player->x > level.width) // le joueur s'est déplacé à la fin du niveau
      level.playerStatus = 2;

    displayUILevel(&interface, cam, level);

    if (level.playerStatus == 1) { // Si le joueur est en jeu
      eventsInLevel(&level, cam);
      executeControls(controls, &level, cam);
      removeLevelBehind(&level, cam.xMin);
      if (cam.xMax < level.width) // on déplace la caméra, si elle n'est pas arrivée à la fin
        translateCamera(&cam, level.speed * level.speedCoeff, 0);
    }

    glPopMatrix();

    SDL_GL_SwapBuffers();


    /* Boucle traitant les événements */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

      switch (e.type) {


        case SDL_VIDEORESIZE: /* On redimensionne le viewport */
          WINDOW_HEIGHT = e.resize.h;
          WINDOW_WIDTH = e.resize.w;
          resizeViewport(cam);
          break;


        case SDL_KEYDOWN: /* Evénements à l'appui d'une touche */

          switch (e.key.keysym.sym) {
            case SDLK_F12: /* Plein écran */
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

            case SDLK_ESCAPE: // touche "échap" pour quitter
              loop = 0;
              break;

            case SDLK_r: // touche "r", recommencer le niveau si le joueur n'est plus en jeu
              if (level.playerStatus != 1) {
                freeLevel(&level);
                level = generateLevelFromFile(levelName);
                cam = initCamera(level.height);
              }
              break;

            default:
              break;
          }

          break;

        case SDL_KEYUP: /* Evénements au relachement d'une touche */

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

  freeLevel(&level);
  freeUi(&interface);
  SDL_Quit();


  return EXIT_SUCCESS;
}
