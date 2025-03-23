/* The GLUT library (GL/glut.h) already includes
   GL/glu.h and GL/gl.h .
   Functions from each library are prefixed by: gl, glu, or glut.

   In Visual Studio: create an empty CPP project, then
   extract the glut library package (containing
   glut.h, glut.lib, glut.dll - or their 32 bit versions).
   Copy them so that the .h and .lib files are in the same directory
   as your .cpp file, and the .dll is together with your .exe .
   If you choose the 32-bit version of files, make sure you're
   also building a 32-bit version of the project.

   On most GNU/Linux distro, MacOS, Codeblocks, Visual Studio Code + mingw:
   GLUT is implelmented by freeglut.
   In the case of Debian / Ubuntu and variants, the packages are
   'freeglut3' and 'freeglut3-dev'.
   Manually building the binary can be done like so:
   g++ -o binary -lGL -lGLU -lglut source.cpp
   Nota bene: GL and GLU are ALLCAPS, glut is not.
   You can also use the enclosed Makefile.
*/

#include <cstdlib>
#include <cmath>
#include <iostream>
// #include "glut.h" //MSVC local library install
#include <GL/glut.h> //system-wide install (or compiler default path)
#include "cg2_lib.h"

const int DEFAULT_WINDOW_W = 800;
const int DEFAULT_WINDOW_H = 800;

unsigned char g_prevKey = '1';

void Display1()
{
  drawGrid(5, 5);
  // draw primitive line as well
  drawBresenhamLine(-5, -5, 5, 3);
  drawBresenhamLine(-5, -5, -2, 6);
}

void Display2()
{
}

void Display3()
{
}

void Display4()
{
}

void Display5()
{
}

void Display6()
{
}

void Display7()
{
}

void Display8()
{
}

void Display(void)
{
  std::cout << "Call Display\n";

  // Clear the buffer. See init();
  glClear(GL_COLOR_BUFFER_BIT);

  switch (g_prevKey)
  {
  case '1':
    Display1();
    break;
  case '2':
    Display2();
    break;
  case '3':
    Display3();
    break;
  case '4':
    Display4();
    break;
  case '5':
    Display5();
    break;
  case '6':
    Display6();
    break;
  case '7':
    Display7();
    break;
  case '8':
    Display8();
    break;
  default:
    std::cerr << "!!! Error in displayCb !!!\n";
    break;
  }

  // forces the image to be sent to the screen
  glFlush();
}

// GLUT CALLBACK: WINDOW RESIZE
void resizeCb(int w, int h)
{
  std::cout << "Window resize. Width: " << w << " height: " << h << std::endl;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  // Set the projection matrix to preserve aspect ratio
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Adjust the orthogonal projection based on the new window size
  if (w <= h)
  {
    // Adjust for portrait aspect ratio
    glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
  }
  else
  {
    // Adjust for landscape aspect ratio
    glOrtho(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
  }

  // Switch back to modelview matrix
  glMatrixMode(GL_MODELVIEW);
}

void keyboardCb(unsigned char key, int x, int y)
{
  std::cout << "Key: " << key << " has been pressed at coordinates: ";
  std::cout << x << " x " << y << std::endl;
  g_prevKey = key;
  if (key == 27) // escape
    exit(0);
  // redraw window
  glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
  std::cout << "Mouse button ";
  std::cout << ((button == GLUT_LEFT_BUTTON) ? "left" : ((button == GLUT_RIGHT_BUTTON) ? "right" : "middle")) << " ";
  std::cout << ((state == GLUT_DOWN) ? "pressed" : "released");
  std::cout << " at coordinates: " << x << " x " << y << std::endl;
}

void initGraphics(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(DEFAULT_WINDOW_W, DEFAULT_WINDOW_H);
  // let window manager decide initial window position
  glutInitWindowPosition(-1, -1);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // argv[0] is window name
  glutCreateWindow(argv[0]);

  // colors and sizes
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(2);
  glPointSize(20);

  // cb's
  glutReshapeFunc(resizeCb);
  glutKeyboardFunc(keyboardCb);
  glutDisplayFunc(Display);
}

int main(int argc, char **argv)
{
  initGraphics(argc, argv);
  glutMainLoop();

  return 0;
}