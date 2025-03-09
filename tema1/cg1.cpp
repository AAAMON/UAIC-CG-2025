#include <iostream>
#include <cmath>
#include <GL/glut.h> 
#include <complex>

const int DEFAULT_WINDOW_W = 1000;
const int DEFAULT_WINDOW_H = 1000;
double g_jfa = -0.82, g_jfb = -0.17; //Julia-Fatou a and b values.

unsigned char prevKey = '1';


class Turtle {
    protected:
        double m_x, m_y;
        double m_angle;
    
    public:
        Turtle(double x = 0, double y = 0):
            m_x(x),
            m_y(y),
            m_angle(0) { }
        
        void rotate(double angle) {
            m_angle += angle;
        }
        
        void move(double distance) {
            //Move the Turtle without drawing.
            /*
            We convert from Radial coordinates
            to Cartesian coordinates.
            */
            m_x += distance * cos(m_angle);
            m_y += distance * sin(m_angle);
        }
        
        void draw(double distance) {
            //Move the Turtle and draw its path.
            glBegin(GL_LINES); {
            glVertex2d(m_x, m_y);
            move(distance);
            glVertex2d(m_x, m_y);
            }
            glEnd();
        }
        
        void resetPos() {m_x = 0; m_y = 0;}
        void resetRotation() {m_angle = 0;}
};

// x and y are middle of current square
// distance = length of current square (NOT THE SQUARE WE'RE DRAWING)
void sierpinskiCarpet(float x, float y, float distance, int maxRecursion)
{
    // DEBUG
    // std::cout << "At center: " << x << ' ' << y << "; with distance =" << distance << '\n';
    distance /= 3;
    // draw square in middle
    Turtle t(x - distance/2, y - distance/2);
    t.draw(distance);
    t.rotate(M_PI/2);
    t.draw(distance);
    t.rotate(M_PI/2);
    t.draw(distance);
    t.rotate(M_PI/2);
    t.draw(distance);

    
    --maxRecursion;
    if (maxRecursion == 0)
        return;

    // go for other sub squares in this order:
    // [1] [2] [3]
    // [4] [ ] [5]
    // [6] [7] [8]
    sierpinskiCarpet(x-distance, y-distance, distance, maxRecursion);
    sierpinskiCarpet(x, y-distance, distance, maxRecursion);
    sierpinskiCarpet(x+distance, y-distance, distance, maxRecursion);

    sierpinskiCarpet(x-distance, y, distance, maxRecursion);
    sierpinskiCarpet(x+distance, y, distance, maxRecursion);

    sierpinskiCarpet(x-distance, y+distance, distance, maxRecursion);
    sierpinskiCarpet(x, y+distance, distance, maxRecursion);
    sierpinskiCarpet(x+distance, y+distance, distance, maxRecursion);
}

// sierpinski carpet fractal
void Display1() {
    int maxRecursion = 4; // +1
    // IDEA /////////////////////////
    // 1. Draw daddy square
    // 2. Draw square from middle
    // 3. If iterations left, get all other subsquares and repeat from 2.

    // Big square
    glColor3f(1, 0, 0);
    // 0,0 e centrul ecranului
    Turtle t0(-0.95, -0.95);
    float distance = 1.9;
    t0.draw(distance);
    t0.rotate(M_PI/2);
    t0.draw(distance);
    t0.rotate(M_PI/2);
    t0.draw(distance);
    t0.rotate(M_PI/2);
    t0.draw(distance);

    sierpinskiCarpet(0, 0, distance, maxRecursion);
  }

// pentagon fractal
void Display2() {

}

void bitmapString(void* font, const char* str) {
    //Draw a string, character-by-character.
    char cp;
    for(const char* c = str; *c != 0; ++c) {
      cp = *c; //to respect const
      glutBitmapCharacter(font, cp);
    }
  }
  
  void drawBitmapString(const char* str, float x = -2, float y = -2) {
    //Draw a string, optionally setting raster position.
    /*
      We define the convetion that both values -2 mean 'do not change
      raster position'.
    */
    if((-2 != x) || (-2 != y)) {
      glRasterPos2f(x, y);
    }
    //freeglut, not old glut: glutBitmapString(GLUT_BITMAP_8_BY_13, str);
    bitmapString(GLUT_BITMAP_8_BY_13, str);
  }
  
  template <typename Numtype>
  void drawBitmapNumber(Numtype number, float x = -2, float y = -2) {
    //Convert a number to a string, then draw it.
    //We need the template so we don't display '2' as '2.000000'.
    if((-2 != x) || (-2 != y)) {
      glRasterPos2f(x, y);
    }
    bitmapString(GLUT_BITMAP_8_BY_13, std::to_string(number).c_str());
  }
  
//   void drawRecursionLevel() {
//     //Simple utility function.
//     drawBitmapString("Recursion Level: ", -0.98, -0.98);
//     /*if we don't set explicit raster positions,
//       drawing characters increments the paster position appropriately
//     */
//     drawBitmapNumber(g_recursionCurrent); 
//   }

  template <typename FloatType>
class JF {
protected:
  //The x and y mathematical bounds of the fractal slice we're displaying.
  FloatType m_xmin, m_xmax, m_ymin, m_ymax;
  //The constant we're biasing the JF fractal with.
  std::complex<FloatType> m_c;
  //The radius around the origin we're using to detect divergence.
  FloatType m_maxRadius;
  //How many iterations we'll do to allow the number sequence to
  //exceed the limit.
  int m_maxIteration;

  virtual inline int test(std::complex<FloatType> z, std::complex<FloatType> c, double maxRadius = 2, int maxIteration = 50) {
    /*
      Compute the Julia-Fatou set in a point in 4D (x, y, a, b). Return the iterations *left*
      upon radius breach. So, a return value of 0 means estimated-divergence, other values
      mean speed of estimated convergence.
    */
    //We create a number sequence, and estimate its limit.
    for(int ii = maxIteration; ii > 0; --ii) {
      z = z * z + c;
      if(abs(z) > maxRadius)
	return(ii);
    }
    return 0;
  }
  
public:
    JF(FloatType xmin, FloatType xmax, FloatType ymin, FloatType ymax, FloatType a = 0, FloatType b = 0, FloatType maxRadius = 20, int maxIteration = 150):
        m_xmin(xmin),
        m_xmax(xmax),
        m_ymin(ymin),
        m_ymax(ymax),
        m_c(a, b),
        m_maxRadius(maxRadius),
        m_maxIteration(maxIteration) {
    }

    void draw(FloatType l, FloatType r, FloatType b, FloatType t, int samplePointsHorizontal, int samplePointsVertical) {

            // Clear the background to white
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background to white (RGBA: 1.0f, 1.0f, 1.0f, 1.0f)
            glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1);
        FloatType stepx = (m_xmax - m_xmin) / FloatType(samplePointsHorizontal);
        FloatType stepy = (m_ymax - m_ymin) / FloatType(samplePointsVertical);
        FloatType steph = (r - l) / FloatType(samplePointsHorizontal);
        FloatType stepv = (t - b) / FloatType(samplePointsVertical);
        int iterations;
        std::complex<FloatType> z;
        glBegin(GL_POINTS);
    
        for (FloatType jj = 0, y = m_ymin, v = b; jj < samplePointsVertical; jj += 1, y += stepy, v += stepv) {
            z.imag(y);
    
            for (FloatType ii = 0, x = m_xmin, h = l; ii < samplePointsHorizontal; ii += 1, x += stepx, h += steph) {
                z.real(x);
                // Pass the current (x, y) as the constant c
                iterations = test(z, std::complex<FloatType>(x, y), m_maxRadius, m_maxIteration);
    
                // If the point is inside the Mandelbrot set (iterations == 0), color it red
                if (iterations == 0) {
                    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for points inside the set
                } else {
                    // Points that are diverging should be white (background)
                    glColor3f(1.0f, 1.0f, 1.0f);  // White color for points outside the set
                }
    
                glVertex2d(h, v);
            }
        }
        glColor3f(1.0f, 0.0f, 0.0f);
        glEnd();
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    
    
    


};


template <typename FloatType>
class MB: public JF<FloatType> {
protected:
  virtual inline int test(std::complex<FloatType> z, std::complex<FloatType> c, double maxRadius = 2, int maxIteration = 50) {
    /*
      Compute the Mandelbrot set for the given point (z, c). Returns the number of iterations before divergence.
      - A return value of 0 means inside the set (red).
      - A return value greater than 0 indicates how fast it diverged (i.e., the number of iterations).
    */

    // Iterate the function z = z^2 + c
    for (int i = 0; i < maxIteration; ++i) {
        // z = z^2 + c
        z = z * z + c;
        
        // If the magnitude of z exceeds the escape radius, it's outside the set
        if (std::abs(z) > maxRadius) {
            return 1; // Return the number of iterations before escaping
        }
    }

    // If it doesn't escape after maxIteration iterations, consider it inside the set (i.e., red)
    return 0;
}



public:
  MB(FloatType xmin, FloatType xmax, FloatType ymin, FloatType ymax, FloatType a = 0, FloatType b = 0, FloatType maxRadius = 2, int maxIteration = 100):
    JF<FloatType>(xmin, xmax, ymin, ymax, a, b, maxRadius, maxIteration) {}

  // You can add additional drawing logic specific to the Mandelbrot set if needed
};




void drawJfConstants() {
    drawBitmapString("Julia-Fatou constants: a = ", -0.98, -0.98);
    drawBitmapNumber(g_jfa);
    drawBitmapString(", b = ");
    drawBitmapNumber(g_jfb);
}

// monochrome mandelbrot
void Display3() {
  //Draw the Mandelbrot fractal here.
  float drawSize = 1.0;
  MB<double> mb(-2, 2, -2, 2);
  /*
    +1 because we're going full-window, and pixel-perfect drawing
    is weird because pixels are actually placed at 0.5 coordinates.
    More on this in the Shaders homework and lecture.
  */
  mb.draw(-drawSize, drawSize, -drawSize, drawSize, DEFAULT_WINDOW_W + 1, DEFAULT_WINDOW_H + 1);
}

// colored mandelbrot
void Display4() {
    
}

// GLUT CALLBACK: WINDOW RESIZE
void resizeCb(int w, int h) {
    std::cout<< "Window resize. Width: " << w << " height: " << h << std::endl;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    // Set the projection matrix to preserve aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Adjust the orthogonal projection based on the new window size
    if (w <= h) {
        // Adjust for portrait aspect ratio
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    } else {
        // Adjust for landscape aspect ratio
        glOrtho(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
    }

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
}
void keyboardCb(unsigned char key, int x, int y) {
    std::cout<< "Key: " << key << " has been pressed at coordinates: ";
    std::cout<< x << " x " << y << std::endl;
    prevKey = key;
    if (key == 27) // escape
      exit(0);
    //redraw window
    glutPostRedisplay();
}
void displayCb(void) {
    std::cout << "Call Display\n";
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);
  
    switch(prevKey) {
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
    default:
        std::cerr << "!!! Error in displayCb !!!\n";
        break;
    }
  
    // forces the image to be sent to the screen
    glFlush();
}

void initGraphics(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(DEFAULT_WINDOW_W, DEFAULT_WINDOW_H);
    // let window manager decide initial window position
    glutInitWindowPosition(-1, -1);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    // argv[0] is window name
    glutCreateWindow (argv[0]);

    // colors and sizes
    glClearColor(1.0,1.0,1.0,1.0);
    glLineWidth(2);
    glPointSize(20);

    // cb's
    glutReshapeFunc(resizeCb);
    glutKeyboardFunc(keyboardCb);
    glutDisplayFunc(displayCb);

}

int main(int argc, char** argv) {
    initGraphics(argc, argv);
    glutMainLoop();

    return 0;
}