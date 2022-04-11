#ifndef OPENGL_HANDSON_SAMPLE02_CAMERA_H
#define OPENGL_HANDSON_SAMPLE02_CAMERA_H

#include <cglm/cglm.h>

struct camera {
  vec3 position;  // meter
  versor quaternion;
  float far_clip;        // meter
  float near_clip;       // meter
  float vertical_fov;    // rad
  float horizontal_fov;  // rad
};

struct camera* camera_create(vec3 position, versor quaternion, float far_clip,
    float near_clip, float vertical_fov, float horizontal_fov);

void camera_destroy(struct camera* camera);

void camera_get_view_projection(struct camera* camera, mat4 matrix);

// right handed / +y is up
//            +y |    / -z
//               |   /
//               |  /
//               | /
//               |/
// -x ------------------------- +x
//              /|
//             / |
//            /  |
//           /   |
//       +z /    | -y

#endif  //  OPENGL_HANDSON_SAMPLE02_CAMERA_H
