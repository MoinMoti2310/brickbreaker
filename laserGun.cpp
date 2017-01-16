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
  gun.rotation_dir = 0;
  gun.angle = angle;
  gun.status = 0;
  gun.rotation_speed = 1;
  LaserObject["gun"] = gun;
}

void createLaser(float x, float y, float w, float h, COLOR color) {
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
  entity laser = {};
  laser.x = x;
  laser.y = y;
  laser.width = 2*w;
  laser.height = 2*h;
  laser.color= color;
  laser.xspeed = 0.05;
  laser.yspeed = 0.05;
  laser.angle = LaserObject["gun"].angle;
  laser.object = object;
  laser.status = 1;
  Laser.push_back(laser);
  for (auto i = Laser.begin(); i != Laser.end(); i++) if (!(*i).status) Laser.erase(i);
}

void laserGunEngine() {
  createGun(-4, 0.0, 1.0, 0.2, 0, grey);
}

void laserEngine() {
  float x = LaserObject["gun"].x + (LaserObject["gun"].width/2.0)*cos(LaserObject["gun"].angle*M_PI/180.0f);
  float y = LaserObject["gun"].y + (LaserObject["gun"].height/2.0)*sin(LaserObject["gun"].angle*M_PI/180.0f);
  createLaser(x, y, 0.2, 0.05, coingold);
}
