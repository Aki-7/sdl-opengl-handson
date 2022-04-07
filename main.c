#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <stdio.h>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <GLUT/glut.h>
#else
#include <SDL2/SDL.h>
#include <GL/gl.h>
#endif

#include <stdbool.h>

int main()
{
  int running = 0;
  SDL_Event event;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window = SDL_CreateWindow("OpenGL Handson", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  (void)ctx;

  const GLubyte *version = glGetString(GL_VERSION);

  fprintf(stdout, "OpenGL Version: %s\n", version);

  glClearColor(0.0, 0.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  running = true;
  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running = false;
        break;

      default:
        break;
      }
    }
    SDL_GL_SwapWindow(window);
  }

  return 0;
}
