#pragma once

#include <GL/glut.h>
#include <cmath>

using namespace std;

 // Task 1 and 3 ////////////////////////////////////////////////////////////////////////////////////////////////////
 void drawGrid(int gridRows, int gridCols) {
    glColor3f(0.8f, 0.8f, 0.8f);
    
    glBegin(GL_LINES);
    for (int i = 0; i <= gridCols; i++) {
        glVertex2i(i, 0);
        glVertex2i(i, gridRows);
    }
    for (int j = 0; j <= gridRows; j++) {
        glVertex2i(0, j);
        glVertex2i(gridCols, j);
    }
    glEnd();
}

// Draws a circular pixel at the corner (x, y)
void drawPixel(int x, int y) {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color

    const float radius = 0.3f; // Smaller radius to avoid touching adjacent corners
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);  // Center at (x, y)
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}


void drawOpenGLLine(int x0, int y0, int x1, int y1) {
    // Set the color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

// Function to draw a line in the first and third octants
void drawLinePositiveSlope(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x1, y1);  // Draw the pixel
        if (x1 == x2 && y1 == y2) break;
        int e2 = err + err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Function to draw a line in the second and fourth octants
void drawLineNegativeSlope(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x1, y1);  // Draw the pixel
        if (x1 == x2 && y1 == y2) break;
        int e2 = err + err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


// Bresenham's Line Algorithm
void drawLine(int x1, int y1, int x2, int y2) {
     // Calculate the slope of the line to determine which octant function to call
     int dx = abs(x2 - x1);
     int dy = abs(y2 - y1);
 
     if (dy <= dx) {
         // Handle lines with a slope of <= 1 (first and third octants)
         drawLinePositiveSlope(x1, y1, x2, y2);
     } else {
         // Handle lines with a slope of > 1 (second and fourth octants)
         drawLineNegativeSlope(x1, y1, x2, y2);
     }
}


// Draw a line with specified thickness using rasterization
// Draw a line with specified thickness using rasterization
void drawThickLine(int x0, int y0, int x1, int y1, int thickness = 1) {
    // If thickness is 1, use the original algorithm
    if (thickness == 1) {
        drawLine(x0, y0, x1, y1);
        return;
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    
    // For a thick line, we need to draw multiple parallel lines
    // Calculate the direction vector of the line
    double len = sqrt(dx*dx + dy*dy);
    double unitX = (x1 - x0) / len;
    double unitY = (y1 - y0) / len;
    
    // Calculate the perpendicular vector
    double perpX = -unitY;
    double perpY = unitX;
    
    // Half thickness (to offset in both directions)
    int halfThick = thickness / 2;
    
    // Draw multiple parallel lines
    for (int i = -halfThick; i <= halfThick; i++) {
        // Calculate starting and ending points for this parallel line
        int startX = round(x0 + perpX * i);
        int startY = round(y0 + perpY * i);
        int endX = round(x1 + perpX * i);
        int endY = round(y1 + perpY * i);
        
        // Draw this line using standard Bresenham
        int dxx = abs(endX - startX);
        int dyy = abs(endY - startY);
        int sxx = (startX < endX) ? 1 : -1;
        int syy = (startY < endY) ? 1 : -1;
        int err = dxx - dyy;
        
        int currX = startX;
        int currY = startY;
        
        while (true) {
            drawPixel(currX, currY);
            
            if (currX == endX && currY == endY) break;
            
            int e2 = 2 * err;
            if (e2 > -dyy) {
                err -= dyy;
                currX += sxx;
            }
            if (e2 < dxx) {
                err += dxx;
                currY += syy;
            }
        }
    }

    drawOpenGLLine(x0, y0, x1, y1);
}

void drawOpenGLCircle(int cx, int cy, int r) {
    // Set the color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);  // Use GL_LINE_LOOP to draw only the contour
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;  // Convert to radians
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw a point in the first octant (top-right quadrant)
void drawOctant1(int cx, int cy, int x, int y) {
    drawPixel(cx + x, cy + y); // Top-right
}

// Function to draw a point in the second octant (top-left quadrant)
void drawOctant2(int cx, int cy, int x, int y) {
    drawPixel(cx - x, cy + y); // Top-left
}

// Function to draw a point in the third octant (bottom-left quadrant)
void drawOctant3(int cx, int cy, int x, int y) {
    drawPixel(cx - x, cy - y); // Bottom-left
}

// Function to draw a point in the fourth octant (bottom-right quadrant)
void drawOctant4(int cx, int cy, int x, int y) {
    drawPixel(cx + x, cy - y); // Bottom-right
}

// Midpoint Circle Algorithm using 4 octant functions
void drawCircle(int cx, int cy, int r) {
    int x = r, y = 0;
    int p = 1 - r;

    while (x >= y) {
        // Draw points for all 8 octants using the functions
        drawOctant1(cx, cy, x, y);  // Top-right
        drawOctant2(cx, cy, x, y);  // Top-left
        drawOctant3(cx, cy, x, y);  // Bottom-left
        drawOctant4(cx, cy, x, y);  // Bottom-right
        
        drawOctant1(cx, cy, y, x);  // Top-right (mirrored)
        drawOctant2(cx, cy, y, x);  // Top-left (mirrored)
        drawOctant3(cx, cy, y, x);  // Bottom-left (mirrored)
        drawOctant4(cx, cy, y, x);  // Bottom-right (mirrored)

        y++;
        if (p <= 0) {
            p += y + y + 1;  // Update error term
        } else {
            x--;
            p += (y - x) + (y - x) + 1;  // Update error term
        }
    }
}


// Draw a circle with specified thickness using rasterization
void drawThickCircle(int cx, int cy, int r, int thickness = 1) {
    // If thickness is 1, use the original algorithm
    if (thickness == 1) {
        drawCircle(cx, cy, r);
        return;
    }

    int halfThick = thickness / 2;

    // Calculate outer and inner radius for thickness
    int outerRadius = r + halfThick;
    int innerRadius = max(r - halfThick, 0);

    // Draw the outer circle (with radius r + thickness/2)
    drawCircle(cx, cy, outerRadius);

    // Draw the inner circle (with radius r - thickness/2)
    if (innerRadius > 0) {
        drawCircle(cx, cy, innerRadius);
    }

    // Fill the region between the outer and inner circles
    // Iterate through the pixels in the bounding box of the outer circle
    for (int y = cy - outerRadius; y <= cy + outerRadius; y++) {
        for (int x = cx - outerRadius; x <= cx + outerRadius; x++) {
            // Calculate distance from center
            int dx = x - cx;
            int dy = y - cy;
            int distanceSquared = dx * dx + dy * dy;

            // Check if the pixel is within the thickened circle (between outer and inner radii)
            if (distanceSquared <= outerRadius * outerRadius && distanceSquared >= innerRadius * innerRadius) {
                drawPixel(x, y);
            }
        }
    }

    // Draw OpenGL circle to compare (as an outline)
    drawOpenGLCircle(cx, cy, r);
}

// Midpoint Circle Algorithm to draw a filled circle
void drawFilledCircle(int cx, int cy, int r) {
    int x = r, y = 0;
    int p = 1 - r;

    while (x >= y) {
        // Draw pixels for all the horizontal lines in each octant
        for (int i = cx - x; i <= cx + x; i++) {
            drawPixel(i, cy + y);  // Bottom side
            drawPixel(i, cy - y);  // Top side
        }
        
        for (int i = cx - y; i <= cx + y; i++) {
            drawPixel(i, cy + x);  // Bottom side
            drawPixel(i, cy - x);  // Top side
        }

        y++;
        if (p <= 0) {
            p += 2 * y + 1;  // Update error term
        } else {
            x--;
            p += 2 * (y - x) + 1;  // Update error term
        }
    }
     // Draw OpenGL circle to compare (as an outline)
     drawOpenGLCircle(cx, cy, r);
}




 // Task 2 ////////////////////////////////////////////////////////////////////////////////////////////////////

