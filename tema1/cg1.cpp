#include <iostream>
#include <GL/glut.h> 

const int DEFAULT_WINDOW_W = 1000;
const int DEFAULT_WINDOW_H = 1000;

unsigned char prevKey;

// square fractal
void Display1() {
    glColor3f(0.2,0.15,0.88); // blue
    glBegin(GL_LINES); { // we'll draw lines; don't forget the ';'
      glVertex2i(1,1); // the coordinates of a vertex (2d, integer coordinates)
      glVertex2i(-1,-1);
    }
    glEnd();
  
    glColor3f(1,0.1,0.1); // red
    glBegin(GL_LINES); {
      glVertex2i(-1,1);
      glVertex2i(1,-1);
    }
    glEnd();
  
    glBegin(GL_LINES); {
      glVertex2d(-0.5,0);
      glVertex2d(0.5,0);
    }
    glEnd();
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
    glLineWidth(3);
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