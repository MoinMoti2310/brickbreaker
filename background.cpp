#include "headerFile.h"

void createCircle (string id, COLOR color, float x, float y, float r, int parts, string component) {
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
    entity bgObject = {};
    bgObject.x = x;
    bgObject.y = y;
    bgObject.color = color;
    bgObject.radius = r;
    bgObject.object = object;
    BackgroundObject[id] = bgObject;
  }

  void createRectangle(string id, float x, float y, float w, float h, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color, float angle) {
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
      a_color.r, a_color.g, a_color.b,
      b_color.r, b_color.g, b_color.b,
      c_color.r, c_color.g, c_color.b,

      c_color.r, c_color.g, c_color.b,
      d_color.r, d_color.g, d_color.b,
      a_color.r, a_color.g, a_color.b,
    };
    VAO * object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
    entity bgObject = {};
    bgObject.x = x;
    bgObject.y = y;
    bgObject.width = 2*w;
    bgObject.height = 2*h;
    bgObject.object = object;
    bgObject.angle = angle;
    bgObject.status = 1;
    BackgroundObject[id] = bgObject;
  }

  void backgroundObjectsEngine () {
    createCircle("sun", sun, -3.0, 3.0, 0.25, 100000, "sun");
    createRectangle("ground", 0.0, -4.0, 8.0, 2.0, brown1, brown1, brown1, brown1, 0);
    createRectangle("bird1up", -2.5, 3.0, 0.5, 0.05, cloudwhite1, cloudwhite1, cloudwhite1, cloudwhite1, 15);
    createRectangle("bird1down", -2.5, 3.0, 0.5, 0.05, cloudwhite1, cloudwhite1, cloudwhite1, cloudwhite1, -15);
  }
