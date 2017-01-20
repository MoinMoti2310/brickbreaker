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
  gun.drag_status = 0;
  gun.up_translation_status = 0;
  gun.down_translation_status = 0;
  gun.rotation_speed = 1;
  LaserObject["gun"] = gun;
}

void createHolder (float x, float y, float r, int parts, COLOR color) {
  GLfloat vertex_buffer_data[parts*9];
  GLfloat color_buffer_data[parts*9];
  int i,j;
  float angle=(2*M_PI/parts);
  float current_angle = 0;
  for(i=0;i<parts;i++){
    for(j=0;j<3;j++){
      color_buffer_data[i*9+j*3]=color.r;
      color_buffer_data[i*9+j*3+1]=color.g;
      color_buffer_data[i*9+j*3+2]=color.b;
    }
    vertex_buffer_data[i*9]=0;
    vertex_buffer_data[i*9+1]=0;
    vertex_buffer_data[i*9+2]=0;
    vertex_buffer_data[i*9+3]=r*cos(current_angle);
    vertex_buffer_data[i*9+4]=r*sin(current_angle);
    vertex_buffer_data[i*9+5]=0;
    vertex_buffer_data[i*9+6]=r*cos(current_angle+angle);
    vertex_buffer_data[i*9+7]=r*sin(current_angle+angle);
    vertex_buffer_data[i*9+8]=0;
    current_angle+=angle;
  }
  VAO * object = create3DObject(GL_TRIANGLES, (parts*9)/3, vertex_buffer_data, color_buffer_data, GL_FILL);

  entity holder = {};
  holder.x = x;
  holder.y = y;
  holder.radius = r;
  holder.color = color;
  holder.object = object;
  holder.drag_status = 0;
  holder.up_translation_status = 0;
  holder.down_translation_status = 0;
  LaserObject["holder"] = holder;
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
  laser.xspeed = 0.1;
  laser.yspeed = 0.1;
  laser.angle = LaserObject["gun"].angle;
  laser.object = object;
  laser.status = 1;
  Laser.push_back(laser);
  for (auto i = Laser.begin(); i != Laser.end(); i++) if (!(*i).status) Laser.erase(i);
}

void laserGunEngine() {
  createGun(-4, 0.0, 1.0, 0.2, 0, grey);
  createHolder(-4.0, 0.0, 0.25, 100000, grey);
}

void laserEngine() {
  current_laser_time = glfwGetTime();
  if (current_laser_time - prev_laser_time > 1) {
    float x = LaserObject["gun"].x + (LaserObject["gun"].width/2.0)*cos(LaserObject["gun"].angle*M_PI/180.0f);
    float y = LaserObject["gun"].y + (LaserObject["gun"].height*2.5)*sin(LaserObject["gun"].angle*M_PI/180.0f);
    createLaser(x, y, 0.2, 0.05, coingold);
    prev_laser_time = glfwGetTime();
  }
}

void dragLaser() {
  float width_diff_gun = x_mouse - LaserObject["gun"].x;
  float height_diff_gun = y_mouse - LaserObject["gun"].y;
  float width_diff_holder = x_mouse - LaserObject["holder"].x;
  float height_diff_holder = y_mouse - LaserObject["holder"].y;
  if (abs(width_diff_gun) < LaserObject["gun"].width/2.0 && abs(height_diff_gun) < LaserObject["gun"].height/2.0) LaserObject["gun"].drag_status = 1;
  else if (abs(width_diff_holder) < LaserObject["holder"].width/2.0 && abs(height_diff_holder) < LaserObject["holder"].height/2.0) LaserObject["holder"].drag_status = 1;
}
