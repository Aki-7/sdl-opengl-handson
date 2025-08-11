#pragma once

#include <GL/glew.h>

struct opengl_square {
  GLuint vao_id;
  GLuint vbo_id;
  GLuint program_id;
};

struct opengl_square *opengl_square_create(void);

void opengl_square_destroy(struct opengl_square *square);

void opengl_square_draw(struct opengl_square *square);
