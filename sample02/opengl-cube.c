#include "opengl-cube.h"

#include <cglm/cglm.h>
#include <handson-util/shader-compiler.h>
#include <stdlib.h>

#define GLSL(str) (const char *)"#version 410\n" #str

static const char *simple_vertex_shader = GLSL(

    uniform mat4 mvp;

    layout(location = 0) in vec4 position;
    void main() { gl_Position = mvp * position; }

);

static const char *simple_fragment_shader = GLSL(

    out vec4 outputColor;
    void main() { outputColor = vec4(1.0, 0.0, 0.0, 1.0); }

);

static void
opengl_cube_fill_buffer(struct opengl_cube *cube)
{
  vec3 vertices[24];

  vec3 p;
  int i = 0;

  for (int j = 0; j < 3; j++) {
    int x = j;
    int y = (j + 1) % 3;
    int z = (j + 2) % 3;
    for (int k = -1; k < 2; k += 2) {
      p[y] = cube->half_size[y] * k;
      for (int l = -1; l < 2; l += 2) {
        p[z] = cube->half_size[z] * l;
        p[x] = cube->half_size[x];
        glm_vec3_copy(p, vertices[i++]);
        p[x] = -cube->half_size[x];
        glm_vec3_copy(p, vertices[i++]);
      }
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, cube->vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

struct opengl_cube *
opengl_cube_create(vec3 half_size, vec3 position, versor quaternion)
{
  struct opengl_cube *cube;

  cube = malloc(sizeof *cube);
  if (cube == NULL) goto err;

  glm_vec3_copy(half_size, cube->half_size);
  glm_vec3_copy(position, cube->position);
  glm_quat_copy(quaternion, cube->quaternion);

  cube->program_id = handson_util_generate_and_compile_opengl_programs(
      simple_vertex_shader, simple_fragment_shader);
  if (cube->program_id == 0) {
    fprintf(stderr, "failed to setup shader programs\n");
    goto err_shader;
  }

  glGenVertexArrays(1, &cube->vao_id);

  glGenBuffers(1, &cube->vbo_id);

  opengl_cube_fill_buffer(cube);

  glBindVertexArray(cube->vao_id);
  glBindBuffer(GL_ARRAY_BUFFER, cube->vbo_id);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return cube;

err_shader:
  free(cube);

err:
  return NULL;
}

void
opengl_cube_destroy(struct opengl_cube *cube)
{
  free(cube);
}

void
opengl_cube_render(struct opengl_cube *cube, struct camera *camera)
{
  mat4 mvp, view_projection, rotate, model = GLM_MAT4_IDENTITY_INIT;

  camera_get_view_projection(camera, view_projection);

  glm_quat_mat4(cube->quaternion, rotate);
  glm_translate(model, cube->position);
  glm_mat4_mul(model, rotate, mvp);
  glm_mat4_mul(view_projection, mvp, mvp);

  glBindVertexArray(cube->vao_id);
  glUseProgram(cube->program_id);
  GLint mvp_matrix_location = glGetUniformLocation(cube->program_id, "mvp");
  glUniformMatrix4fv(mvp_matrix_location, 1, GL_FALSE, (float *)mvp);
  glDrawArrays(GL_LINES, 0, 24);
  glUseProgram(0);
  glBindVertexArray(0);
}

void
opengl_cube_rotate(
    struct opengl_cube *cube, float angle /*radian*/, float x, float y, float z)
{
  versor quat;
  glm_quat(quat, angle, x, y, z);
  glm_quat_mul(cube->quaternion, quat, cube->quaternion);
}
