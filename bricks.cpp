#include "headerFile.h"


/*
// Creates the triangle object used in this sample code
void createTriangle () {
//   ONLY vertices between the bounds specified in glm::ortho will be visible on screen

//  Define vertex array as used in glBegin (GL_TRIANGLES)
  static const GLfloat vertex_buffer_data [] = {
    0, 1,0, // vertex 0
    -1,-1,0, // vertex 1
    1,-1,0, // vertex 2
  };

  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 0
    0,1,0, // color 1
    0,0,1, // color 2
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_LINE);
}

// Creates the rectangle object used in this sample code
void createRectangle () {
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
    -1.2,-1,0, // vertex 1
    -1,-1,0, // vertex 2
    -1, 1,0, // vertex 3

    -1, 1,0, // vertex 3
    -1.2, 1,0, // vertex 4
    -1.2,-1,0  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
    1,0,0, // color 1
    0,0,1, // color 2
    0,1,0, // color 3

    0,1,0, // color 3
    0.3,0.3,0.3, // color 4
    1,0,0  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}
*/
void createBricks (int id, float x, float y, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color, float w, float h) {
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
  entity brick = {};
  brick.x = x;
  brick.y = y;
  brick.object = object;
  brick.width = w;
  brick.height = h;
  Brick[id] = brick;
}

void brickEngine(int quantity) {
  for (int i = 0; i < quantity; i++) {
    auto value = rand();
    float x = -2 + value%6;
    float y = 5.5 + i;
    COLOR color;
    if (value % 3 < 2) color = (value % 3) ? red : black;
    else color = darkgreen;
    createBricks(i, x, y, color, color, color, color, 0.1, 0.2);
  }
}
