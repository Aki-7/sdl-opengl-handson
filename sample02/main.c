#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <stdio.h>

#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SDL2/SDL.h>
#else
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on
#include <SDL2/SDL.h>
#endif

#include <cglm/cglm.h>
#include <stdbool.h>

#include "camera.h"
#include "opengl-cube.h"

static vec3 camera_position = {0.0, 0.0, 1.0};
static versor camera_quaternion = GLM_QUAT_IDENTITY_INIT;
static float camera_far_clip = 1000.0;
static float camera_near_clip = 0.01;
static float camera_vertical_fov = M_PI_2 * 2 / 3;
static float camera_horizontal_fov = M_PI_2 * 2 / 3;

static vec3 cube_half_size = {1.0, 1.0, 1.0};
static vec3 cube_position = {0.0, 0.0, -3.0};
static versor cube_quaternion = GLM_QUAT_IDENTITY_INIT;

static int view_width = 640;
static int view_height = 640;

int
main()
{
  int running = 0;
  int exit_code = 1;
  SDL_Event event;
  SDL_Window *window;
  SDL_GLContext *ctx;

  struct camera *camera;
  struct opengl_cube *cube;

  // Initialize OpenGL context
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    goto err;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow("OpenGL Handson", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, view_width, view_height, SDL_WINDOW_OPENGL);
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

  glViewport(0, 0, view_width, view_height);

  // Initialize objects
  // glm_quat(camera_quaternion, M_PI_2 / 9, 0.0, 1.0, 0.0);
  camera = camera_create(camera_position, camera_quaternion, camera_far_clip,
      camera_near_clip, camera_vertical_fov, camera_horizontal_fov);

  // glm_quat(cube_quaternion, M_PI_2 / 3, 1.0, 0.0, 0.0);
  cube = opengl_cube_create(cube_half_size, cube_position, cube_quaternion);

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

    opengl_cube_rotate(cube, M_PI / 120, 0.0, 1.0, 0.0);
    opengl_cube_render(cube, camera);

    SDL_GL_SwapWindow(window);
  }

  exit_code = 0;

err:
  SDL_Quit();

  return exit_code;
}
