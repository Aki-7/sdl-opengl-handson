#pragma once

#ifdef __APPLE__
#include <GL/glew.h>
#else
// clang-format off
#include <GL/glew.h>
// clang-format on
#endif

// OpenGL context and glew must be initialized first
GLuint handson_util_generate_and_compile_opengl_programs(
    const char *vertex_shader_source, const char *fragment_shader_source);
