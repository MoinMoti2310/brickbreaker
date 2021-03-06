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
  createRectangle("bird1up", -2.5, 3.0, 0.5, 0.02, cloudwhite1, cloudwhite1, cloudwhite1, cloudwhite1, 15);
  createRectangle("bird1down", -2.5, 3.0, 0.5, 0.02, cloudwhite1, cloudwhite1, cloudwhite1, cloudwhite1, -15);

}

void createLed(string id, float x, float y, float w, float h, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color, float angle) {
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
  entity led = {};
  led.x = x;
  led.y = y;
  led.width = 2*w;
  led.height = 2*h;
  led.object = object;
  led.status = 0;
  Led[id] = led;
}

void ledEngine() {
  createLed("led1top", 1, 3.5, 0.2, 0.05, scorecolor, scorecolor ,scorecolor, scorecolor, 0);
  createLed("led1middle", 1, 3.3, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led1bottom", 1, 3.1, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led1left1", 0.9, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led1right1", 1.1, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led1left2", 0.9, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor,0);
  createLed("led1right2", 1.1, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);

  createLed("led2top", 0.7, 3.5, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2middle", 0.7, 3.3, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2bottom", 0.7, 3.1, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2left1", 0.6, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2right1", 0.8, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2left2", 0.6, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led2right2", 0.8, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);

  createLed("led3top", 0.4, 3.5, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3middle", 0.4, 3.3, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3bottom", 0.4, 3.1, 0.2, 0.05, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3left1", 0.3, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3right1", 0.5, 3.4, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3left2", 0.3, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);
  createLed("led3right2", 0.5, 3.2, 0.05, 0.2, scorecolor, scorecolor, scorecolor, scorecolor, 0);

}

void resetLed() {
  for (auto i = Led.begin(); i != Led.end(); i++) {
    string current = i->first;
    Led[current].status = 0;
  }
}

void setLed1(char val){
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6'|| val=='7' || val=='8' || val=='9' || val=='P' || val=='I' || val=='O' || val=='N' || val=='T' || val=='S' || val=='E'){
    Led["led1top"].status=1;
  }
  if(val=='2' || val=='3' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='S' || val=='Y' || val=='E'){
    Led["led1middle"].status=1;
  }
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6' || val=='8' || val=='9' || val=='O' || val=='S' || val=='I' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led1bottom"].status=1;
  }
  if(val=='0' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led1left1"].status=1;
  }
  if(val=='0' || val=='2' || val=='6' || val=='8' || val=='P' || val=='O' || val=='N' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led1left2"].status=1;
  }
  if(val=='0' || val=='1' || val=='2' || val=='3' || val=='4' || val=='7' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='Y' || val=='U' || val=='W'){
    Led["led1right1"].status=1;
  }
  if(val=='0' || val=='1' || val=='3' || val=='4' || val=='5' || val=='6' || val=='7' || val=='8' || val=='9' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='W'){
    Led["led1right2"].status=1;
  }
  // if(val=='I' || val=='T'){
  //   Led["led1middle1"].status=1;
  // }
  // if(val=='I' || val=='T' || val=='W'){
  //   Led["led1middle2"].status=1;
  // }
}

void setLed2(char val) {
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6'|| val=='7' || val=='8' || val=='9' || val=='P' || val=='I' || val=='O' || val=='N' || val=='T' || val=='S' || val=='E'){
    Led["led2top"].status=1;
  }
  if(val=='2' || val=='3' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='S' || val=='Y' || val=='E'){
    Led["led2middle"].status=1;
  }
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6' || val=='8' || val=='9' || val=='O' || val=='S' || val=='I' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led2bottom"].status=1;
  }
  if(val=='0' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led2left1"].status=1;
  }
  if(val=='0' || val=='2' || val=='6' || val=='8' || val=='P' || val=='O' || val=='N' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led2left2"].status=1;
  }
  if(val=='0' || val=='1' || val=='2' || val=='3' || val=='4' || val=='7' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='Y' || val=='U' || val=='W'){
    Led["led2right1"].status=1;
  }
  if(val=='0' || val=='1' || val=='3' || val=='4' || val=='5' || val=='6' || val=='7' || val=='8' || val=='9' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='W'){
    Led["led2right2"].status=1;
  }
  // if(val=='I' || val=='T'){
  //   Led["led2middle1"].status=1;
  // }
  // if(val=='I' || val=='T' || val=='W'){
  //   Led["led2middle2"].status=1;
  // }
}

void setLed3(char val) {
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6'|| val=='7' || val=='8' || val=='9' || val=='P' || val=='I' || val=='O' || val=='N' || val=='T' || val=='S' || val=='E'){
    Led["led3top"].status=1;
  }
  if(val=='2' || val=='3' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='S' || val=='Y' || val=='E'){
    Led["led3middle"].status=1;
  }
  if(val=='0' || val=='2' || val=='3' || val=='5' || val=='6' || val=='8' || val=='9' || val=='O' || val=='S' || val=='I' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led3bottom"].status=1;
  }
  if(val=='0' || val=='4' || val=='5' || val=='6' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led3left1"].status=1;
  }
  if(val=='0' || val=='2' || val=='6' || val=='8' || val=='P' || val=='O' || val=='N' || val=='U' || val=='L' || val=='E' || val=='W'){
    Led["led3left2"].status=1;
  }
  if(val=='0' || val=='1' || val=='2' || val=='3' || val=='4' || val=='7' || val=='8' || val=='9' || val=='P' || val=='O' || val=='N' || val=='Y' || val=='U' || val=='W'){
    Led["led3right1"].status=1;
  }
  if(val=='0' || val=='1' || val=='3' || val=='4' || val=='5' || val=='6' || val=='7' || val=='8' || val=='9' || val=='O' || val=='N' || val=='S' || val=='Y' || val=='U' || val=='W'){
    Led["led3right2"].status=1;
  }
  // if(val=='I' || val=='T'){
  //   Led["led3middle1"].status=1;
  // }
  // if(val=='I' || val=='T' || val=='W'){
  //   Led["led3middle2"].status=1;
  // }
}
