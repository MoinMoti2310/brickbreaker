#include "headerFile.h"

void createGun(float x, float y, float w, float h, float angle, COLOR color) {
  w = w/2;
  h = h/2;
  GLfloat vertex_buffer_data [] = {
    -w,-h,0, // vertex 1
    -w,h,0, // vertex 2
    w,h,0, // vertex 3

    w,h,0, // vertex 3
    w,-h,0, // vertex 4
    -w,-h,0  // vertex 1
  };

  GLfloat color_buffer_data [] = {
    // color for respective vertices;
    color.r, color.g, color.b,
    color.r, color.g, color.b,
    color.r, color.g, color.b,

    color.r, color.g, color.b,
    color.r, color.g, color.b,
    color.r, color.g, color.b,
  };
  VAO * object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
  entity gun = {};
  gun.x = x;
  gun.y = y;
  gun.object = object;
  gun.width = 2*w;
  gun.height = 2*h;
  gun.color = color;
  LaserObject["gun"] = gun;
}

void laserGunEngine() {
  createGun(-4.0, 0.0, 1.0, 0.5, 0, grey);
}
