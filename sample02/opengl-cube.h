#pragma once

#include <GL/glew.h>
#include <cglm/cglm.h>

struct camera;

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

void opengl_cube_draw(struct opengl_cube *cube, struct camera *camera);

void opengl_cube_rotate(struct opengl_cube *cube, float angle /*radian*/,
    float x, float y, float z);
