#include "opengl-square.h"

#include <cglm/cglm.h>

#include "stdlib.h"

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
print_shader_compilation_error_log(GLuint shader_id)
{
  int log_length = 0;
  glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

  char log_message[log_length];
  glGetShaderInfoLog(shader_id, log_length, NULL, log_message);

  fprintf(stderr, "%s", log_message);
}

static int
compile_opengl_program(GLuint program_id, const char *source, int shader_type)
{
  GLuint shader_id = glCreateShader(shader_type);
  glShaderSource(shader_id, 1, &source, NULL);
  glCompileShader(shader_id);

  GLint shader_compiled = GL_FALSE;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);
  if (shader_compiled != GL_TRUE) {
    print_shader_compilation_error_log(shader_id);
    glDeleteShader(shader_id);
    return -1;
  }
  glAttachShader(program_id, shader_id);
  glDeleteShader(shader_id);
  return 0;
}

static int
link_program(GLuint program_id)
{
  GLint link_success = GL_FALSE;

  glLinkProgram(program_id);

  glGetProgramiv(program_id, GL_LINK_STATUS, &link_success);
  if (link_success != GL_TRUE) {
    int log_length = 0;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

    char log_message[log_length];
    glGetProgramInfoLog(program_id, log_length, NULL, log_message);

    fprintf(stderr, "%s", log_message);

    return -1;
  }

  return 0;
}

static GLuint
generate_and_compile_opengl_programs(
    const char *vertex_shader_source, const char *fragment_shader_source)
{
  GLuint id = glCreateProgram();

  if (vertex_shader_source == NULL || fragment_shader_source == NULL) return -1;

  if (compile_opengl_program(id, vertex_shader_source, GL_VERTEX_SHADER) != 0) {
    glDeleteProgram(id);
    return 0;
  }

  if (compile_opengl_program(id, fragment_shader_source, GL_FRAGMENT_SHADER) !=
      0) {
    glDeleteProgram(id);
    return 0;
  }

  if (link_program(id) != 0) {
    glDeleteProgram(id);
    return 0;
  }

  return id;
}

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

  square->program_id = generate_and_compile_opengl_programs(
      simple_vertex_shader, simple_fragment_shader);
  if (square->program_id == 0) {
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
