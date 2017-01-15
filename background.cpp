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
    entity circle = {};
    circle.x = x;
    circle.y = y;
    circle.color = color;
    circle.radius = r;
    circle.object = object;
    BackgroundObject[id] = circle;
  }

  void backgroundObjectsEngine () {
    createCircle("sun", sun, -3.0, 3.0, 0.5, 100000, "sun");
  }
