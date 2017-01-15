#include "headerFile.h"

void createBaskets(string id, float x, float y, float w, float h, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color) {
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
  entity basket = {};
  basket.x = x;
  basket.y = y;
  basket.object = object;
  basket.width = w;
  basket.height = h;
  basket.left_translation_status = 0;
  basket.right_translation_status = 0;
  Basket[id] = basket;
}

void basketEngine() {
  createBaskets("left", -2.0, -3.5, 0.4, 0.2, red, red, red, red);
  createBaskets("right", 2.0, -3.5, 0.4, 0.2, darkgreen, darkgreen, darkgreen, darkgreen);
}
