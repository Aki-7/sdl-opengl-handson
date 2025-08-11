#ifndef OPENGL_HANDSON_SAMPLE02_OPENGL_CUBE_H
#define OPENGL_HANDSON_SAMPLE02_OPENGL_CUBE_H

#include <cglm/cglm.h>

#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SDL.h>
#else
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on
#include <SDL.h>
#endif

#include "camera.h"

struct opengl_cube {
  vec3 half_size;  // meter
  vec3 position;   // meter
  versor quaternion;

  GLuint vao_id;
  GLuint vbo_id;
  GLuint program_id;
};

struct opengl_cube *opengl_cube_create(
    vec3 half_size, vec3 position, versor quaternion);

void opengl_cube_destroy(struct opengl_cube *cube);

void opengl_cube_render(struct opengl_cube *cube, struct camera *camera);

void opengl_cube_rotate(struct opengl_cube *cube, float angle /*radian*/,
    float x, float y, float z);

#endif  //  OPENGL_HANDSON_SAMPLE02_OPENGL_CUBE_H
