#include "opengl-square.h"

#include <SDL.h>
#include <cglm/cglm.h>
#include <handson-util/shader-compiler.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
// clang-format off
#include <GL/gl.h>
// clang-format on
#endif

vec3 vertices[] = {
    {+0.5, +0.5, 0},
    {+0.5, -0.5, 0},
    {+0.5, -0.5, 0},
    {-0.5, -0.5, 0},
    {-0.5, -0.5, 0},
    {-0.5, +0.5, 0},
    {-0.5, +0.5, 0},
    {+0.5, +0.5, 0},
};

static const char *simple_vertex_shader =
    "#version 410\n"
    "layout(location = 0) in vec4 position;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = position;\n"
    "}\n";

static const char *simple_fragment_shader =
    "#version 410 core\n"
    "out vec4 outputColor;\n"
    "void main()\n"
    "{\n"
    "  outputColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

static void
opengl_square_fill_buffer(struct opengl_square *square)
{
  glBindBuffer(GL_ARRAY_BUFFER, square->vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

struct opengl_square *
opengl_square_create(void)
{
  struct opengl_square *square;

  square = malloc(sizeof *square);
  if (square == NULL) goto err;

  square->program_id = handson_util_generate_and_compile_opengl_programs(
      simple_vertex_shader, simple_fragment_shader);
  if (square->program_id <= 0) {
    fprintf(stderr, "failed to setup shader programs\n");
    goto err_shader;
  }

  glGenVertexArrays(1, &square->vao_id);

  glGenBuffers(1, &square->vbo_id);

  opengl_square_fill_buffer(square);

  glBindVertexArray(square->vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, square->vbo_id);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return square;

err_shader:
  free(square);

err:
  return NULL;
}

void
opengl_square_destroy(struct opengl_square *square)
{
  glDeleteProgram(square->program_id);
  glDeleteBuffers(1, &square->vbo_id);
  glDeleteVertexArrays(1, &square->vao_id);
  free(square);
}

void
opengl_square_draw(struct opengl_square *square)
{
  glBindVertexArray(square->vao_id);
  glUseProgram(square->program_id);
  glDrawArrays(GL_LINES, 0, sizeof vertices / sizeof vertices[0]);
  glUseProgram(0);
  glBindVertexArray(0);
}
