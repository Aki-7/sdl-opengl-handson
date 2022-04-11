#ifndef OPENGL_HANDSON_UTIL_SHADER_COMPILER_H
#define OPENGL_HANDSON_UTIL_SHADER_COMPILER_H

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

// OpenGL context and glew must be initialized first
GLuint handson_util_generate_and_compile_opengl_programs(
    const char *vertex_shader_source, const char *fragment_shader_source);

#endif  //  OPENGL_HANDSON_UTIL_SHADER_COMPILER_H
