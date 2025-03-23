#pragma once

#include <GL/glut.h>
#include <cmath>

float circle = atan(1) * 8;     // 2 * PI = TAU
float halfCircle = atan(1) * 4; // PI

/* THE BIG TO-DO LIST
 * Task 1: correct grid logic
 * Task 1: Circle primitive remains filled regardless of vertices order, idk how to fix
 * Task 1: "You must draw lines thicker than 1 disc" ?????????
 * Task 2: test with new grid logic + eventual corrections (check lecture #2 slides)
 * Task 3: all of it
 */

 // Task 1 ////////////////////////////////////////////////////////////////////////////////////////////////////

void drawGrid(int grid_w, int grid_h)
{
    glColor3f(0.8f, 0.8f, 0.8f); // gray

    glBegin(GL_LINES);
    {
        for (int x = -grid_w / 2; x <= grid_w / 2; x++) // vertical lines
        {
            glVertex2f(x, -grid_h / 2);
            glVertex2f(x, grid_h / 2);
        }

        for (int y = -grid_h / 2; y <= grid_h / 2; y++) // horizontal lines
        {
            glVertex2f(-grid_w / 2, y);
            glVertex2f(grid_w / 2, y);
        }
    }
    glEnd();
}

void drawPixel(int x, int y, float radius = 0.02f) // draws a disc at coordinates (x, y)
{
    glColor3f(0.0f, 0.0f, 0.0f); // black

    // see original cg0 file: display4()
    int maxSteps = 360;
    // A polygon, taking as many points as we give it.
    // In this case, glBegin draws a single geometric figure.
    glBegin(GL_POLYGON);
    {
        for (int ii = 0; ii < maxSteps; ++ii)
        {
            float normalisedPosition = ii / float(maxSteps);
            float angle = -normalisedPosition * circle;
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    }
    glEnd();
}

void drawLine(float x0, float y0, float x1, float y1) // drawing the geometric primitives (lines)
{
    glColor3f(0.0f, 0.0f, 1.0f); // blue

    glBegin(GL_LINES);
    {
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    }
    glEnd();
}

void drawCircle(int x, int y, float radius = 0.5f) // draws the geometric primitives (circle)
{
    glColor3f(0.0f, 0.0f, 1.0f); // blue

    // see original cg0 file: display4()
    int maxSteps = 360;
    // A polygon, taking as many points as we give it.
    // In this case, glBegin draws a single geometric figure.
    glBegin(GL_POLYGON);
    {
        for (int ii = 0; ii < maxSteps; ++ii)
        {
            float normalisedPosition = ii / float(maxSteps);
            float angle = normalisedPosition * circle;
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    }
    glEnd();
}

 // Task 2 ////////////////////////////////////////////////////////////////////////////////////////////////////

void drawLineLow(int x0, int y0, int x1, int y1) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if (dy < 0) 
    {
        yi = -1;
        dy = -dy;
    }

    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++) 
    {
        drawPixel(x, y); // Draw pixel
        if (D > 0) 
        {
            y += yi;
            D -= (2 * dx);
        }
        D += (2 * dy);
    }
}

void drawLineHigh(int x0, int y0, int x1, int y1) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;

    if (dx < 0) 
    {
        xi = -1;
        dx = -dx;
    }

    int D = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++) 
    {
        drawPixel(x, y); // Draw pixel
        if (D > 0) 
        {
            x += xi;
            D -= (2 * dy);
        }
        D += (2 * dx);
    }
}

void drawBresenhamLine(int x0, int y0, int x1, int y1) 
{
    if (abs(y1 - y0) < abs(x1 - x0)) 
    {
        if (x0 > x1) 
            drawLineLow(x1, y1, x0, y0); 
        else
            drawLineLow(x0, y0, x1, y1);
    } 
    else 
    {
        if (y0 > y1) 
            drawLineHigh(x1, y1, x0, y0); 
        else
            drawLineHigh(x0, y0, x1, y1);
    }
}

 // Task 3 ////////////////////////////////////////////////////////////////////////////////////////////////////