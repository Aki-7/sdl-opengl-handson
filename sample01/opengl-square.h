#ifndef OPENGL_HANDSON_SAMPLE01_OPENGL_SQUARE
#define OPENGL_HANDSON_SAMPLE01_OPENGL_SQUARE

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

struct opengl_square {
  GLuint vao_id;
  GLuint vbo_id;
  GLuint program_id;
};

struct opengl_square *opengl_square_create();

void opengl_square_destroy(struct opengl_square *square);

void opengl_square_draw(struct opengl_square *square);

#endif  //  OPENGL_HANDSON_SAMPLE01_OPENGL_SQUARE
