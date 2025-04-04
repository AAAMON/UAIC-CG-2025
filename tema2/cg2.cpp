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
#include <vector>
// #include "glut.h" //MSVC local library install
#include <GL/glut.h> //system-wide install (or compiler default path)
#include "cg2_lib.h"

const int DEFAULT_WINDOW_W = 800;
const int DEFAULT_WINDOW_H = 800;


#define GRID_SIZE 20  // Grid cell size in pixels

int windowWidth = 800, windowHeight = 800;
int gridRows, gridCols;

unsigned char g_prevKey = '1';

void Display1()
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawGrid(gridRows, gridCols);
  drawThickLine(2, 15, 27, 18, 3); // Example line
  drawThickCircle(20, 20, 17, 3);   // Example circle
  drawPixel(5, 5);       // Example pixel
  glutSwapBuffers();
}

void Display2()
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawGrid(gridRows, gridCols);
  drawFilledCircle(20, 20, 17);
  glutSwapBuffers();
}

void Display3()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid(gridRows, gridCols);

    drawThickLine(2, 20, 7, 7, 3);
    drawThickLine(7, 7, 20, 2, 3);
    drawThickLine(20, 2, 33, 7, 3);
    drawThickLine(33, 7, 38, 20, 3);

    drawThickLine(2, 20, 7, 33, 3);
    drawThickLine(7, 33, 20, 38, 3);
    drawThickLine(20, 38, 33, 33, 3);
    drawThickLine(33, 33, 38, 20, 3);

    glutSwapBuffers();
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

// Ensures cells remain square when resizing
void resizeCb(int width, int height) {
  windowWidth = width;
  windowHeight = height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gridCols = width / GRID_SIZE;
  gridRows = height / GRID_SIZE;

  gluOrtho2D(0, gridCols, 0, gridRows);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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