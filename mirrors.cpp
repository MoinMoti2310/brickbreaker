#include "headerFile.h"

void createMirror(float x, float y, float w, float h, COLOR color, float angle) {
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
  entity mirror = {};

  mirror.x = x;
  mirror.y = y;
  mirror.width = 2*w;
  mirror.height = 2*h;
  mirror.object = object;
  mirror.color = color;
  mirror.angle = angle;
  Mirror.push_back(mirror);
}

void  mirrorEngine() {
  createMirror(0.0, 2.0, 0.5, 0.05, cloudwhite, 0);
  createMirror(2.0, 2.0, 0.5, 0.05, cloudwhite, -75);
  createMirror(2.0, -2.0, 0.5, 0.05, cloudwhite, 75);
  createMirror(0.0, -2.0, 0.5, 0.05, cloudwhite, 0);
}

void checkReflection() {
  for (auto i = Mirror.begin(); i != Mirror.end(); i++) {
    for (auto j = Laser.begin(); j != Laser.end(); j++) {
      float current_hit_time = glfwGetTime();
      if ((*j).status && current_hit_time - j->hit_time > 0.5) {
        float slope = (j->y - i->y)/(j->x - i->x);
        float distance = (j->y - i->y)*(j->y - i->y) + (j->x - i->x)*(j->x - i->x);
        float angle_diff = i->angle - j->angle;
        if ((slope - tan(i->angle*M_PI/180.0f)) < 0.01 && distance < (i->width)*(i->width)/4.0) {
          j->angle = 2*angle_diff;
          j->hit_time = glfwGetTime();
        }
      }
    }
  }
}
