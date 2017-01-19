#include "headerFile.h"

struct GLMatrices {
  glm::mat4 projection;
  glm::mat4 model;
  glm::mat4 view;
  GLuint MatrixID;
} Matrices;

GLuint programID;

vector <entity> Brick;
map <string, entity> Basket;
map <string, entity> BackgroundObject;
map <string, entity> LaserObject;
vector <entity> Laser;
vector <entity> Mirror;

float camera_rotation_angle = 90;
float current_laser_time = glfwGetTime();
float prev_laser_time = 0;
double x_mouse, y_mouse;
float x_change = 0;
float y_change = 0;
float zoom_camera = 1;

COLOR grey = {168.0/255.0,168.0/255.0,168.0/255.0};
COLOR silver = {192.0/255.0,192.0/255.0,192.0/255.0};
COLOR sun = {233.0/255.0,189.0/255.0,21.0/255.0};
COLOR gold = {218.0/255.0,165.0/255.0,32.0/255.0};
COLOR coingold = {255.0/255.0,223.0/255.0,0.0/255.0};
COLOR red = {255.0/255.0,51.0/255.0,51.0/255.0};
COLOR lightgreen = {57/255.0,230/255.0,0/255.0};
COLOR darkgreen = {51/255.0,102/255.0,0/255.0};
COLOR black = {30/255.0,30/255.0,21/255.0};
COLOR blue = {0,0,1};
COLOR darkbrown = {46/255.0,46/255.0,31/255.0};
COLOR lightbrown = {95/255.0,63/255.0,32/255.0};
COLOR brown1 = {117/255.0,78/255.0,40/255.0};
COLOR brown2 = {134/255.0,89/255.0,40/255.0};
COLOR brown3 = {46/255.0,46/255.0,31/255.0};
COLOR cratebrown = {153/255.0,102/255.0,0/255.0};
COLOR cratebrown1 = {121/255.0,85/255.0,0/255.0};
COLOR cratebrown2 = {102/255.0,68/255.0,0/255.0};
COLOR skyblue2 = {113/255.0,185/255.0,209/255.0};
COLOR skyblue1 = {123/255.0,201/255.0,227/255.0};
COLOR skyblue = {132/255.0,217/255.0,245/255.0};
COLOR cloudwhite = {229/255.0,255/255.0,255/255.0};
COLOR cloudwhite1 = {204/255.0,255/255.0,255/255.0};
COLOR lightpink = {255/255.0,122/255.0,173/255.0};
COLOR darkpink = {255/255.0,51/255.0,119/255.0};
COLOR white = {255/255.0,255/255.0,255/255.0};
COLOR score = {117/255.0,78/255.0,40/255.0};

/**************************
* Customizable functions *
**************************/

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods) {
  // Function is called first on GLFW_PRESS.

  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_A:
      for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
        string current = i->first;
        LaserObject[current].up_translation_status = 0;
      }
      break;
      case GLFW_KEY_Z:
      for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
        string current = i->first;
        LaserObject[current].down_translation_status = 0;
      }
      break;
      case GLFW_KEY_X:
      // do something ..
      break;
      case GLFW_KEY_LEFT_CONTROL:
      Basket["red"].left_translation_status = 0;
      break;
      case GLFW_KEY_RIGHT_CONTROL:
      Basket["red"].right_translation_status = 0;
      break;
      case GLFW_KEY_LEFT_ALT:
      Basket["green"].left_translation_status = 0;
      break;
      case GLFW_KEY_RIGHT_ALT:
      Basket["green"].right_translation_status = 0;
      break;
      case GLFW_KEY_PAGE_UP:
      LaserObject["gun"].rotation_dir = 0;
      case GLFW_KEY_PAGE_DOWN:
      LaserObject["gun"].rotation_dir = 0;
      break;
      case GLFW_KEY_LEFT:
      x_change -= 0.3;
      checkPan();
      break;
      case GLFW_KEY_RIGHT:
      x_change += 0.3;
      checkPan();
      break;
      case GLFW_KEY_DOWN:
      y_change -= 0.3;
      checkPan();
      break;
      case GLFW_KEY_UP:
      y_change += 0.3;
      checkPan();
      break;
      default:
      break;
    }
  } else if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_A:
      for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
        string current = i->first;
        LaserObject[current].up_translation_status = 1;
      }
      break;
      case GLFW_KEY_Z:
      for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
        string current = i->first;
        LaserObject[current].down_translation_status = 1;
      }
      break;
      case GLFW_KEY_ESCAPE:
      quit(window);
      break;
      case GLFW_KEY_LEFT_CONTROL:
      Basket["red"].left_translation_status = 1;
      break;
      case GLFW_KEY_RIGHT_CONTROL:
      Basket["red"].right_translation_status = 1;
      break;
      case GLFW_KEY_LEFT_ALT:
      Basket["green"].left_translation_status = 1;
      break;
      case GLFW_KEY_RIGHT_ALT:
      Basket["green"].right_translation_status = 1;
      break;
      case GLFW_KEY_PAGE_UP:
      LaserObject["gun"].rotation_dir = 1;
      break;
      case GLFW_KEY_PAGE_DOWN:
      LaserObject["gun"].rotation_dir = -1;
      break;
      case GLFW_KEY_SPACE:
      laserEngine();
      break;
      default:
      break;
    }
  }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key) {
  switch (key) {
    case 'Q':
    case 'q':
    quit(window);
    break;
    default:
    break;
  }
}

void mousescroll(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset==-1) {
        zoom_camera /= 1.1; //make it bigger than current size
    }
    else if(yoffset==1){
        zoom_camera *= 1.1; //make it bigger than current size
    }
    if (zoom_camera<=1) {
        zoom_camera = 1;
    }
    if (zoom_camera>=4) {
        zoom_camera=4;
    }
    if(x_change-4.0f/zoom_camera<-4)
        x_change=-4+4.0f/zoom_camera;
    else if(x_change+4.0f/zoom_camera>4)
        x_change=4-4.0f/zoom_camera;
    if(y_change-4.0f/zoom_camera<-4)
        y_change=-4+4.0f/zoom_camera;
    else if(y_change+4.0f/zoom_camera>4)
        y_change=4-4.0f/zoom_camera;
    Matrices.projection = glm::ortho((float)(-4.0f/zoom_camera+x_change), (float)(4.0f/zoom_camera+x_change), (float)(-4.0f/zoom_camera+y_change), (float)(4.0f/zoom_camera+y_change), 0.1f, 500.0f);
}

//Ensure the panning does not go out of the map
void checkPan() {
    if(x_change-4.0f/zoom_camera<-4)
        x_change=-4+4.0f/zoom_camera;
    else if(x_change+4.0f/zoom_camera>4)
        x_change=4-4.0f/zoom_camera;
    if(y_change-4.0f/zoom_camera<-4)
        y_change=-4+4.0f/zoom_camera;
    else if(y_change+4.0f/zoom_camera>4)
        y_change=4-4.0f/zoom_camera;
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
    if (action == GLFW_PRESS) {
      glfwGetCursorPos(window, &x_mouse, &y_mouse);
      x_mouse -= 300;
      y_mouse -= 300;
      x_mouse = x_mouse*4.0/300.0;
      y_mouse = -y_mouse*4.0/300.0;
//      cout << x_mouse << "|" << y_mouse << endl;
      if (y_mouse > -3.0) LaserObject["gun"].angle = atan((LaserObject["gun"].y - y_mouse)/(LaserObject["gun"].x - x_mouse))*180.0f/M_PI;
      else dragBasket();
    }
    if (action == GLFW_RELEASE) {
      if (y_mouse > -3.0) laserEngine();
      else {
        Basket["red"].status = 0;
        Basket["green"].status = 0;
      }
    }
    break;
    case GLFW_MOUSE_BUTTON_RIGHT:
    if (action == GLFW_PRESS)
    if (action == GLFW_RELEASE)
    break;
    default:
    break;
  }
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height) {
  int fbwidth=width, fbheight=height;
  /* With Retina display on Mac OS X, GLFW's FramebufferSize
  is different from WindowSize */
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);

  GLfloat fov = 90.0f;

  // sets the viewport of openGL renderer
  glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

  // set the projection matrix as perspective
  /* glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
  // Store the projection matrix in a variable for future use
  // Perspective projection for 3D views
  // Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

  // Ortho projection for 2D views
  Matrices.projection = glm::ortho(-4.0f/zoom_camera+x_change, 4.0f/zoom_camera+x_change, -4.0f/zoom_camera+y_change, 4.0f/zoom_camera+y_change, 0.1f, 500.0f);
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw (GLFWwindow* window) {

  Matrices.projection = glm::ortho(-4.0f/zoom_camera+x_change, 4.0f/zoom_camera+x_change, -4.0f/zoom_camera+y_change, 4.0f/zoom_camera+y_change, 0.1f, 500.0f);

  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
  // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //  Don't change unless you are sure!!
  Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  //  Don't change unless you are sure!!
  glm::mat4 VP = Matrices.projection * Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  //  Don't change unless you are sure!!
  glm::mat4 MVP;	// MVP = Projection * View * Model

  for (auto i = BackgroundObject.begin(); i != BackgroundObject.end(); i++) {
    string current = i->first;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3(BackgroundObject[current].x, BackgroundObject[current].y, 0.0f));
    glm::mat4 rotateObject = glm::rotate((float)(BackgroundObject[current].angle*M_PI/180.0f), glm::vec3(0,0,1));
    glm::mat4 objectTransform = translateObject*rotateObject;
    Matrices.model *= objectTransform;
    MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(BackgroundObject[current].object);
  }

  if (BackgroundObject["bird1up"].status) {
    BackgroundObject["bird1up"].angle -= 1;
    BackgroundObject["bird1down"].angle += 1;
    if (BackgroundObject["bird1up"].angle == -15.0) BackgroundObject["bird1up"].status = 0;
  } else {
    BackgroundObject["bird1up"].angle += 1;
    BackgroundObject["bird1down"].angle -= 1;
    if (BackgroundObject["bird1up"].angle == 15.0) BackgroundObject["bird1up"].status = 1;
  }

  for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
    string current = i->first;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3(LaserObject[current].x, LaserObject[current].y, 0.0f));
    glm::mat4 rotateObject = glm::rotate((float)(LaserObject[current].angle*M_PI/180.0f), glm::vec3(0,0,1));
    glm::mat4 objectTransform = translateObject*rotateObject;
    Matrices.model *= objectTransform;
    MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(LaserObject[current].object);
  }

  for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
    string current = i->first;
    LaserObject[current].y += (LaserObject[current].up_translation_status) ? 0.01 : 0;
    LaserObject[current].y -= (LaserObject[current].down_translation_status) ? 0.01 : 0;
  }

  for (auto i = LaserObject.begin(); i != LaserObject.end(); i++) {
    string current = i->first;
    LaserObject[current].angle += LaserObject[current].rotation_speed*LaserObject[current].rotation_dir;
  }

  for (auto i = Basket.begin(); i != Basket.end(); i++) {
    string current = i->first;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3(Basket[current].x, Basket[current].y, 0.0f));
    Matrices.model *= translateObject;
    MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(Basket[current].object);
  }

  Basket["red"].x -= (Basket["red"].left_translation_status) ? 0.01 : 0;
  Basket["green"].x -= (Basket["green"].left_translation_status) ? 0.01 : 0;
  Basket["red"].x += (Basket["red"].right_translation_status) ? 0.01 : 0;
  Basket["green"].x += (Basket["green"].right_translation_status) ? 0.01 : 0;

  if (Basket["red"].status) {
    float width_diff_red = x_mouse - Basket["red"].x;
    glfwGetCursorPos(window, &x_mouse, &y_mouse);
    x_mouse -= 300;
    y_mouse -= 300;
    x_mouse = x_mouse*4.0/300.0;
    y_mouse = -y_mouse*4.0/300.0;
    Basket["red"].x = x_mouse - width_diff_red;
  }

  if (Basket["green"].status) {
    float width_diff_green = x_mouse - Basket["green"].x;
    glfwGetCursorPos(window, &x_mouse, &y_mouse);
    x_mouse -= 300;
    y_mouse -= 300;
    x_mouse = x_mouse*4.0/300.0;
    y_mouse = -y_mouse*4.0/300.0;
    Basket["green"].x = x_mouse - width_diff_green;
  }

  for (auto i = Mirror.begin(); i != Mirror.end(); i++) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3((*i).x, (*i).y, 0.0f));
    glm::mat4 rotateObject = glm::rotate((float)((*i).angle*M_PI/180.0f), glm::vec3(0,0,1));
    Matrices.model *= translateObject*rotateObject;
    MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject((*i).object);
  }

  for (auto i = Brick.begin(); i != Brick.end(); i++) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3((*i).x, (*i).y, 0.0f));
    Matrices.model *= translateObject;
    MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject((*i).object);
  }

  float translation_increments = 0.03;

  for (auto i = Brick.begin(); i != Brick.end(); i++) {
    if ((*i).y < -5) {
      Brick.erase(i);
      brickEngine(1);
    } else (*i).y = (*i).y - translation_increments;
  }

  for (auto i = Laser.begin(); i != Laser.end(); i++) {
    if ((*i).status) {
      Matrices.model = glm::mat4(1.0f);
      glm::mat4 translateObject = glm::translate(glm::vec3((*i).x, (*i).y, 0.0f));
      glm::mat4 rotateObject = glm::rotate((float)((*i).angle*M_PI/180.0f), glm::vec3(0,0,1));
      glm::mat4 objectTransform = translateObject*rotateObject;
      Matrices.model *= objectTransform;
      MVP = VP * Matrices.model;
    }

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject((*i).object);
  }

  for (auto i = Laser.begin(); i != Laser.end(); i++) {
    if ((*i).status) {
      if ((*i).y < -3 || (*i).y > 5 || (*i).x > 5 || (*i).x < -4) (*i).status = 0;
      else {
        (*i).x += ((*i).xspeed)*cos((*i).angle*M_PI/180.0f);
        (*i).y += ((*i).yspeed)*sin((*i).angle*M_PI/180.0f);
      }
    }
  }

}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height) {
  GLFWwindow* window; // window desciptor/handle

  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    //        exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

  if (!window) {
    glfwTerminate();
    //        exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval( 1 );

  /* --- register callbacks with GLFW --- */

  /* Register function to handle window resizes */
  /* With Retina display on Mac OS X GLFW's FramebufferSize
  is different from WindowSize */
  glfwSetFramebufferSizeCallback(window, reshapeWindow);
  glfwSetWindowSizeCallback(window, reshapeWindow);

  /* Register function to handle window close */
  glfwSetWindowCloseCallback(window, quit);

  /* Register function to handle keyboard input */
  glfwSetKeyCallback(window, keyboard);      // general keyboard input
  glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

  /* Register function to handle mouse click */
  glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks
  glfwSetScrollCallback(window, mousescroll);

  return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height) {
  /* Objects should be created before any other gl function and shaders */
  // Create the models
  //  createTriangle (); // Generate the VAO, VBOs, vertices data & copy into the array buffer
  //  createRectangle ();
  backgroundObjectsEngine();
  laserGunEngine();
  basketEngine();
  mirrorEngine();
  brickEngine(10);
  // Create and compile our GLSL program from the shaders
  programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
  // Get a handle for our "MVP" uniform
  Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


  reshapeWindow (window, width, height);

  // Background color of the scene
  glClearColor (skyblue.r, skyblue.g, skyblue.b, 0.0f); // R, G, B, A
  glClearDepth (1.0f);

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);

  cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
  cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
  cout << "VERSION: " << glGetString(GL_VERSION) << endl;
  cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv) {
  int width = 600;
  int height = 600;

  srand((unsigned)time(0));

  GLFWwindow* window = initGLFW(width, height);

  initGL (window, width, height);

  double last_update_time = glfwGetTime(), current_time;

  /* Draw in loop */
  while (!glfwWindowShouldClose(window)) {

    // OpenGL Draw commands
    draw(window);

    checkCollisionBrick();
    checkReflection();

    // Swap Frame Buffer in double buffering
    glfwSwapBuffers(window);

    // Poll for Keyboard and mouse events
    glfwPollEvents();

    // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
    current_time = glfwGetTime(); // Time in seconds
    if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
      // do something every 0.5 seconds ..
      last_update_time = current_time;
    }
  }

  glfwTerminate();
  //    exit(EXIT_SUCCESS);
}
