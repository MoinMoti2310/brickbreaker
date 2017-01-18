#ifndef headerFile
#define headerFile

#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct VAO {
  GLuint VertexArrayID;
  GLuint VertexBuffer;
  GLuint ColorBuffer;

  GLenum PrimitiveMode;
  GLenum FillMode;
  int NumVertices;
};
typedef struct VAO VAO;

typedef struct COLOR {
  float r;
  float g;
  float b;
}COLOR;

extern COLOR grey;
extern COLOR silver;
extern COLOR sun;
extern COLOR gold;
extern COLOR coingold;
extern COLOR red;
extern COLOR lightgreen;
extern COLOR darkgreen;
extern COLOR black;
extern COLOR blue;
extern COLOR darkbrown;
extern COLOR lightbrown;
extern COLOR brown1;
extern COLOR brown2;
extern COLOR brown3;
extern COLOR cratebrown;
extern COLOR cratebrown1;
extern COLOR cratebrown2;
extern COLOR skyblue2;
extern COLOR skyblue1;
extern COLOR skyblue;
extern COLOR cloudwhite;
extern COLOR cloudwhite1;
extern COLOR lightpink;
extern COLOR darkpink;
extern COLOR white;
extern COLOR score;

typedef struct entity {
  string id;
  int type;
  COLOR color;
  float x, y;
  float radius;
  float angle;
  float rotation_speed;
  int rotation_dir;
  VAO *object;
  int status;
  float height, width;
  float xspeed, yspeed;
  bool left_translation_status;
  bool right_translation_status;
  int value;
}entity;

extern vector <entity> Brick;
extern map <string, entity> Basket;
extern map <string, entity> BackgroundObject;
extern map <string, entity> LaserObject;
extern vector <entity> Laser;
extern vector <entity> Mirror;

extern struct GLMatrices Matrices;

extern GLuint programID;
extern float camera_rotation_angle;
extern float current_laser_time;
extern float prev_laser_time;
extern double x_mouse, y_mouse;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}
void quit(GLFWwindow *window);
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode);
struct VAO* create3DObject (GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode);
void draw3DObject (struct VAO* vao);
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods);
void keyboardChar (GLFWwindow* window, unsigned int key);
void mouseButton (GLFWwindow* window, int button, int action, int mods);
void reshapeWindow (GLFWwindow* window, int width, int height);
void createTriangle ();
void createRectangle ();
void draw (GLFWwindow* window);
GLFWwindow* initGLFW (int width, int height);
void initGL (GLFWwindow* window, int width, int height);
void createBricks (int id, float x, float y, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color, float w, float h);
void brickEngine(int quantity);
void createBaskets(string id, float x, float y, float w, float h, COLOR a_color, COLOR b_color, COLOR c_color, COLOR d_color);
void basketEngine();
void createCircle (string id, COLOR color, float x, float y, float r, int parts, string component);
void backgroundObjectsEngine();
void checkCollisionBrick();
void createGun(float x, float y, float w, float h, float angle, COLOR color);
void laserGunEngine();
void createLaser();
void laserEngine();
void mirrorEngine();
void createMirror(float x, float y, float w, float h, COLOR color, float angle);
void checkReflection();
void dragBasket();
void mousescroll(GLFWwindow* window, double xoffset, double yoffset);
void check_pan();


#endif
