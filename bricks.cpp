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
void createBricks (int type, int value, float x, float y, COLOR color, float w, float h) {
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
  entity brick = {};
  brick.x = x;
  brick.y = y;
  brick.type = type;
  brick.color = color;
  brick.object = object;
  brick.width = 2*w;
  brick.height = 2*h;
  brick.value = value;
  Brick.push_back(brick);
}

void brickEngine(int quantity) {
  for (int i = 0; i < quantity; i++) {
    auto rand_value = rand();
    float x = -2 + rand_value%6;
    float y = 5.5 + i;
    COLOR color;
    int type;
    int brick_value = 10;
    if (rand_value % 3 < 2) {
      color = (rand_value % 3) ? red : black;
      type = (rand_value %  3) ? 1 : 0;
    } else {
      color = darkgreen;
      type = 2;
    }
    if (rand_value % 50 == 0) {
      color = silver;
      type = 0;
      brick_value = 50;
    }
    if (rand_value % 100 == 0) {
      color = gold;
      type = 0;
      brick_value = 100;
    }
    createBricks(type, brick_value, x, y, color, 0.2, 0.4);
  }
}

void checkCollisionBrick() {
  float width_diff, height_diff, min_h_diff, min_w_diff;
  for (auto i = Brick.begin(); i != Brick.end(); i++) {
    if (i->type == 1) {
      height_diff = abs(i->y - Basket["red"].y);
      width_diff = abs(i->x - Basket["red"].x);
      min_h_diff = (i->height + Basket["red"].height)/2.0;
      min_w_diff = (i->width + Basket["red"].width)/2.0;
      if (height_diff < min_h_diff && width_diff < min_w_diff) {
        Brick.erase(i);
        brickEngine(1);
      }
    } else if (i->type == 2) {
      height_diff = abs(i->y - Basket["green"].y);
      width_diff = abs(i->x - Basket["green"].x);
      min_h_diff = (i->height + Basket["green"].height)/2.0;
      min_w_diff = (i->width + Basket["green"].width)/2.0;
      if (height_diff < min_h_diff && width_diff < min_w_diff) {
        Brick.erase(i);
        brickEngine(1);
      }
    }
  }
}
