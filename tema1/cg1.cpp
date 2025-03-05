#include <iostream>
#include <cmath>
#include <GL/glut.h> 

const int DEFAULT_WINDOW_W = 1000;
const int DEFAULT_WINDOW_H = 1000;

unsigned char prevKey = '1';


class Turtle {
    /*
      Turtle Graphics:
      draw using points, directions and distances.
      (Radial coordinates.)
    */
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
    // go for other sub squares
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

// monochrome mandelbrot
void Display3() {
    
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