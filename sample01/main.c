#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <stdio.h>

#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SDL2/SDL.h>
#else
#include <GL/gl.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#endif

#include <stdbool.h>

#include "opengl-square.h"

int
main()
{
  int running = 0;
  int exit_code = 1;
  int width = 640, height = 480;
  SDL_Event event;
  SDL_Window *window;
  SDL_GLContext *ctx;
  struct opengl_square *square = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    goto err;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow("OpenGL Handson", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    fprintf(stderr, "Unable to create SDL window\n");
    goto err;
  }

  ctx = SDL_GL_CreateContext(window);
  if (ctx == NULL) {
    fprintf(stderr, "Unable to create GL context by SDL\n");
    goto err;
  }

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Unable to initialize GLEW\n");
    goto err;
  }

  fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));

  square = opengl_square_create();
  if (square == NULL) {
    fprintf(stderr, "Unable to create a opengl_square object\n");
    goto err;
  }

  glViewport(0, 0, width, height);

  running = true;
  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;

        default:
          break;
      }
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    opengl_square_draw(square);

    SDL_GL_SwapWindow(window);
  }

  exit_code = 0;

err:
  if (square) opengl_square_destroy(square);

  SDL_Quit();

  return exit_code;
}
