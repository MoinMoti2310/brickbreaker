#include "headerFile.h"

void createBaskets(string id, float x, float y, float w, float h, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color) {
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
  entity basket = {};
  basket.x = x;
  basket.y = y;
  basket.object = object;
  basket.width = 2*w;
  basket.height = 2*h;
  basket.left_translation_status = 0;
  basket.right_translation_status = 0;
  basket.status = 0;
  Basket[id] = basket;
}

void basketEngine() {
  createBaskets("red", -2.0, -3.5, 0.8, 0.4, red, red, red, red);
  createBaskets("green", 2.0, -3.5, 0.8, 0.4, darkgreen, darkgreen, darkgreen, darkgreen);
}

void dragBasket() {
  float width_diff_red = x_mouse - Basket["red"].x;
  float height_diff_red = y_mouse - Basket["red"].y;
  float width_diff_green = x_mouse - Basket["green"].x;
  float height_diff_green = y_mouse - Basket["green"].y;
  if (abs(width_diff_red) < Basket["red"].width/2.0 && abs(height_diff_red) < Basket["red"].height/2.0) Basket["red"].status = 1;
  else if (abs(width_diff_green) < Basket["green"].width/2.0 && abs(height_diff_green) < Basket["green"].height/2.0) Basket["green"].status = 1;
}
