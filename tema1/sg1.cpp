/*
  This program plots different 2D functions.
*/

#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <utility>
#include <vector>
//#include "glut.h" //MSVC local library install
#include <GL/glut.h> //system-wide install (or compiler default path)

using namespace std;

double circle = atan(1) * 8;
double halfCircle = atan(1) * 4;
double tau = circle;    // 2 * PI = TAU
double pi = halfCircle; // TAU / 2 = PI

// How often should the drawing algorithm sample the function.
double step = 0.05;



int defaultW = 800, defaultH = 800;

unsigned char prevKey;

///////////////////////////////////////////////////////////////////////////////////////
// 1. /////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Function to calculate the distance from x to the nearest integer (d(x))
double d(double x)
{
  return fabs(x - round(x));
}
void Display1()
{
  // IN ENUNT ZICE PANA LA 100 DAR IN IMAGINEA DE PE SITE APARE UN RANGE MAI MIC (EG. 30)
  double xmax = 30;  // x in the range [0, 100]
  double ymax = 1.0; // F(x) = d(x)/x will have a maximum value of 1.0 as x increases

  // Scale factor to shrink the graph slightly and leave margin space
  double scaleX = 0.9; // Shrink the X-axis to 90% of the window width
  double scaleY = 0.8; // Shrink the Y-axis to 80% of the window height

  glColor3f(1, 0.1, 0.1); // Use the same color as in the original code (red)
  glBegin(GL_LINE_STRIP);

  for (double x = 0; x <= xmax; x += step)
  {
    double y;

    if (x == 0)
    {
      y = 1; // F(0) = 1
    }
    else
    {
      y = d(x) / x; // F(x) = d(x) / x for x > 0
    }

    // Scale x and y values to fit the screen with margins
    double xScaled = x / xmax * scaleX;
    double yScaled = y / ymax * scaleY;

    glVertex2d(xScaled, yScaled);
  }

  glEnd();
}

///////////////////////////////////////////////////////////////////////////////////////
// 2.1 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Function to plot the graph using function arguments f(a, b, t)
// asta e defapt punctul 3
void plot(double (*x)(double, double, double), double (*y)(double, double, double),
          double a, double b, double intervalStart, double intervalEnd,
          double step, double scaleX, double scaleY, GLint primitive)
{
  glBegin(primitive);
  for (double t = intervalStart; t < intervalEnd; t += step)
  {
    double xVal = (*x)(a, b, t); // Calculate x using the provided function
    double yVal = (*y)(a, b, t); // Calculate y using the provided function

    // Scale x and y values
    xVal = xVal * scaleX;
    yVal = yVal * scaleY;

    glVertex2d(xVal, yVal); // Plot the point
  }
  glEnd();
}

// Limaçon (Pascal's Snail) equations
double xLimacon(double a, double b, double t)
{
  return 2 * (a * cos(t) + b) * cos(t); // x(t) = 2 * (a * cos(t) + b) * cos(t)
}

double yLimacon(double a, double b, double t)
{
  return 2 * (a * cos(t) + b) * sin(t); // y(t) = 2 * (a * cos(t) + b) * sin(t)
}

void Display2()
{
  double a = 0.3, b = 0.2;
  double intervalStart = -pi, intervalEnd = pi;
  double step = 0.01;
  double scaleX = 0.9, scaleY = 0.8; // Shrinking the graph a bit for better visibility

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Use plot function to plot Limaçon (Pascal's Snail)
  glColor3f(1, 0.1, 0.1); // Set color to red
  plot(xLimacon, yLimacon, a, b, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 2.2 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Cycloid equations
double xCycloid(double a, double b, double t)
{
  return a * t - b * sin(t); // x(t) = a * t - b * sin(t)
}

double yCycloid(double a, double b, double t)
{
  return a - b * cos(t); // y(t) = a - b * cos(t)
}

void Display3()
{
  double a = 0.1, b = 0.2;
  double intervalStart = 0, intervalEnd = 10 * pi; // Display a range of t from 0 to 10 * pi (arbitrary choice)
  double step = 0.01;

  // Shrink the graph slightly by scaling
  double scaleX = 0.5, scaleY = 0.5;

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Apply translation to move the graph to the left
  glPushMatrix();               // Save the current matrix
  glTranslatef(-0.8, 0.0, 0.0); // Translate by -0.5 on the x-axis (move left)

  // Use plot function to plot Cycloid
  glColor3f(1, 0.1, 0.1); // Set color to red
  plot(xCycloid, yCycloid, a, b, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glPopMatrix(); // Restore the previous matrix

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 2.3 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Epicicloid equations
double xEpicicloid(double a, double b, double t)
{
  return (a + b) * cos((b / a) * t) - b * cos(t + (b / a) * t); // x(t) = (a + b) * cos(b/a * t) - b * cos(t + b/a * t)
}

double yEpicicloid(double a, double b, double t)
{
  return (a + b) * sin((b / a) * t) - b * sin(t + (b / a) * t); // y(t) = (a + b) * sin(b/a * t) - b * sin(t + b/a * t)
}

void Display4()
{
  double a = 0.1, b = 0.3;
  double intervalStart = 0, intervalEnd = 2 * pi; // Display a range of t from 0 to 2 * pi
  double step = 0.01;

  // Shrink the graph slightly by scaling
  double scaleX = 0.8, scaleY = 0.8;

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Use plot function to plot Epicicloid
  glColor3f(1, 0.1, 0.1); // Set color to red
  plot(xEpicicloid, yEpicicloid, a, b, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 2.4 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Hipocicloid equations
double xHipocicloid(double a, double b, double t)
{
  return (a - b) * cos((b / a) * t) - b * cos(t - (b / a) * t); // x(t) = (a - b) * cos(b/a * t) - b * cos(t - b/a * t)
}

double yHipocicloid(double a, double b, double t)
{
  return (a - b) * sin((b / a) * t) - b * sin(t - (b / a) * t); // y(t) = (a - b) * sin(b/a * t) - b * sin(t - b/a * t)
}

void Display5()
{
  double a = 0.1, b = 0.3;
  double intervalStart = 0, intervalEnd = 2 * pi; // Display a range of t from 0 to 2 * pi
  double step = 0.01;

  // Shrink the graph slightly by scaling
  double scaleX = 1.6, scaleY = 1.6;

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Use plot function to plot Hipocicloid
  glColor3f(1, 0.1, 0.1); // Set color to red
  plot(xHipocicloid, yHipocicloid, a, b, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 4.1 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Logarithmic spiral equation (polar to Cartesian conversion)
double xLogSpiral(double a, double b, double t)
{
  double r = a * exp(1 + t); // r(t) = a * e^(1 + t)
  return r * cos(t);         // x(t) = r(t) * cos(t)
}

double yLogSpiral(double a, double b, double t)
{
  double r = a * exp(1 + t); // r(t) = a * e^(1 + t)
  return r * sin(t);         // y(t) = r(t) * sin(t)
}

void Display6()
{
  double a = 0.02;                           // Given value for a
  double intervalStart = 0, intervalEnd = 4; // Limiting t to avoid runaway growth
  double step = 0.01;

  // Shrink the graph slightly by scaling
  double scaleX = 0.4, scaleY = 0.4;

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Use plot function to plot Logarithmic Spiral
  glColor3f(1, 0, 0); // Set color to red
  plot(xLogSpiral, yLogSpiral, a, 0, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 4.2 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Sine polar flower equation (polar to Cartesian conversion)
double xSinePolarFlower(double a, double b, double t)
{
  double r = sin(a * t); // r(t) = sin(a * t)
  return r * cos(t);     // x(t) = r(t) * cos(t)
}

double ySinePolarFlower(double a, double b, double t)
{
  double r = sin(a * t); // r(t) = sin(a * t)
  return r * sin(t);     // y(t) = r(t) * sin(t)
}

void Display7()
{
  double a = 10;                                       // Given value for a
  double intervalStart = 0, intervalEnd = 2 * pi * 10; // Full pattern range, 2 * pi * a to complete all petals
  double step = 0.01;

  // Shrink the graph slightly by scaling
  double scaleX = 0.7, scaleY = 0.7;

  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

  // Use plot function to plot the Sine Polar Flower
  glColor3f(1, 0, 0); // Set color to red
  plot(xSinePolarFlower, ySinePolarFlower, a, 0, intervalStart, intervalEnd, step, scaleX, scaleY, GL_LINE_STRIP);

  glutSwapBuffers(); // Swap buffers to display the result
}

///////////////////////////////////////////////////////////////////////////////////////
// 5 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
const float a = 0.2f;
vector<pair<float, float>> computeCurve(float scale) {
  vector<pair<float, float>> points;
  float dt = 0.01f; // Step size for t

  // Define limits to avoid stretching to edges
  float x_limit = 0.5f * scale;
  float y_limit = 0.5f * scale;

  for (float t = -pi / 2 + dt; t < -pi / 6; t += dt) {
      float cos_t = cos(t);
      float denominator = 4 * cos_t * cos_t - 3;

      if (abs(denominator) < 1e-5) continue; // Avoid division by zero

      float x = a / denominator;
      float y = (a * tan(t)) / denominator;

      // Ensure the point belongs to the top-left leaf (x < 0, y > 0)
      // AND stays within the predefined limits
      if (abs(x) < x_limit && abs(y) < y_limit) {
          points.emplace_back(x * scale, y * scale); // Apply scaling
      }
  }
  return points;
}

void Display8() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 0.0f, 0.0f); // Red curve

  float scale = 1.3f; // Adjust for zooming, but empty space remains
  vector<pair<float, float>> points = computeCurve(scale);

  if (points.empty()) return; // Safety check

  // Define the upper-left corner of the window scaled by the 'scale' factor
  float x_max = -1.0f / 1.23; // Scaled left of the screen
  float y_max = 1.0f / 1.25;  // Scaled top of the screen

  // Get the leftmost point from the curve
  float x_curve_min = points.front().first;
  float y_curve_min = points.front().second;

  // Draw filled shape from top-left to the curve
  glColor3f(1.0f, 0.5f, 0.5f); // Light red fill
 // Draw solid color alternating triangles
glBegin(GL_TRIANGLES);
for (size_t i = 0; i < points.size() - 1; ++i) {
    // Alternate colors for each triangle
    if (i % 2 == 0) {
        glColor3f(1.0f, 0.5f, 0.5f); // Red
    } else {
        glColor3f(1.0f, 1.0f, 1.0f); // White
    }

    // Draw each triangle: (x_max, y_max) to two consecutive points
    glVertex2f(x_max, y_max);            // Top-left corner (fixed vertex)
    glVertex2f(points[i].first, points[i].second); // Current curve point
    glVertex2f(points[i + 1].first, points[i + 1].second); // Next curve point
}

glEnd();

  // Draw curve outline
  glColor3f(1.0f, 0.0f, 0.0f); // Red outline
  glBegin(GL_LINE_STRIP);
  for (const auto& p : points) {
      glVertex2f(p.first, p.second);
  }
  glEnd();

  glFlush();
}


void Display9()
{
}
void Display10()
{
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(2);
  glPointSize(1);
  // glPolygonMode(GL_FRONT, GL_LINE);
  // Enabling blending and smoothing
  glEnable(GL_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_NICEST, GL_POINT_SMOOTH_HINT);
  glHint(GL_NICEST, GL_LINE_SMOOTH_HINT);
  glHint(GL_NICEST, GL_POLYGON_SMOOTH_HINT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void Display(void) {
  cout<<("Call Display")<<endl;
  // Clear the buffer. See init();
  glClear(GL_COLOR_BUFFER_BIT);

  switch (prevKey)
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
  case '9':
    Display9();
    break;
  case '0':
    Display10();
    break;
  default:
    break;
  }
  glFlush();
}

void Reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void KeyboardFunc(unsigned char key, int x, int y)
{
  prevKey = key;
  if (key == 27) // escape
    exit(0);
  // The proper way to ask glut to redraw the window.
  glutPostRedisplay();
}

/*
  Callback upon mouse press or release.
  The button can be:
  GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
  (and further for mousewheel and other mouse buttons)
  The state can be either GLUT_DOWN or  GLUT_UP, for
  a pressed or released button.
  (x, y) are the coordinates of the mouse.
*/
void MouseFunc(int button, int state, int x, int y) {
  cout<< "Mouse button ";
  cout<<( (button == GLUT_LEFT_BUTTON) ? "left" : ((button == GLUT_RIGHT_BUTTON) ? "right": "middle") ) << " ";
  cout<< ( (state == GLUT_DOWN) ? "pressed" : "released" );
  cout<< " at coordinates: " << x <<" x " << y << endl;
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(defaultW, defaultH);
  glutInitWindowPosition(-1, -1);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow(argv[0]);
  init();
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(KeyboardFunc);
  glutMouseFunc(MouseFunc);
  glutDisplayFunc(Display);
  // glutIdleFunc(Display);
  glutMainLoop();

  return 0;
}