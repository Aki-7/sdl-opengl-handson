#include <handson-util/shader-compiler.h>

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

GLuint
handson_util_generate_and_compile_opengl_programs(
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
