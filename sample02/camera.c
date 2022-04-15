#include "camera.h"

#include <stdlib.h>

struct camera*
camera_create(vec3 position, versor quaternion, float far_clip, float near_clip,
    float vertical_fov, float horizontal_fov)
{
  struct camera* camera;

  camera = malloc(sizeof *camera);
  if (camera == NULL) goto err;

  glm_vec3_copy(position, camera->position);
  glm_quat_copy(quaternion, camera->quaternion);
  camera->far_clip = far_clip;
  camera->near_clip = near_clip;
  camera->vertical_fov = vertical_fov;
  camera->horizontal_fov = horizontal_fov;

  return camera;

err:
  return NULL;
}

void
camera_destroy(struct camera* camera)
{
  free(camera);
}

void
camera_get_view_projection(struct camera* camera, mat4 matrix)
{
  float a = 1 / tanf(camera->horizontal_fov / 2);
  float b = 1 / tanf(camera->vertical_fov / 2);
  float n_f = camera->near_clip - camera->far_clip;
  float c = camera->far_clip / n_f;
  float d = camera->far_clip * camera->near_clip / n_f;

  // column major
  mat4 projection = {
      {a, 0, 0, 0},   //
      {0, b, 0, 0},   //
      {0, 0, c, -1},  //
      {0, 0, d, 0},   //
  };

  mat4 rotate, translate = GLM_MAT4_IDENTITY_INIT, view;
  vec4 position_inv;
  versor quaternion_inv;

  glm_vec3_inv_to(camera->position, position_inv);
  glm_quat_inv(camera->quaternion, quaternion_inv);

  glm_quat_mat4(quaternion_inv, rotate);
  glm_translate(translate, position_inv);

  // view = rotate (camera quat inv) * translate (camera pos inv)
  glm_mat4_mul(rotate, translate, view);

  // view_projection = projection * view
  glm_mat4_mul(projection, view, matrix);
}
