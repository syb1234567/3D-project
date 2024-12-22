#include <windows.h>
#include "C:/Users/lenovo/source/repos/OpenGLproject/OpenGLproject/include/glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cfloat> // For FLT_MAX
#include <cmath>
#include <map>

// Coordinates for the main body (black)
GLfloat black[][2] = {
    {-0.6, 1.0}, {0.3, 1.0},
    {-0.6, 0.9}, {-0.5, 0.9}, {0.2, 0.9}, {0.3, 0.9},
    {-0.6, 0.8}, {-0.4, 0.8}, {0.1, 0.8}, {0.3, 0.8},
    {-0.6, 0.7}, {-0.4, 0.7}, {-0.3, 0.7}, {-0.2, 0.7}, {-0.1, 0.7}, {0.0, 0.7}, {0.1, 0.7}, {0.3, 0.7},
    {-0.6, 0.6}, {0.3, 0.6},
    {-0.6, 0.5}, {0.3, 0.5},
    {-0.7, 0.4}, {-0.4, 0.4}, {0.1, 0.4}, {0.4, 0.4},
    {-0.7, 0.3}, {-0.4, 0.3}, {0.1, 0.3}, {0.4, 0.3},
    {-0.7, 0.2}, {-0.2, 0.2}, {-0.1, 0.2}, {0.4, 0.2},
    {-0.6, 0.1}, {0.3, 0.1},
    {-0.5, 0.0}, {-0.4, 0.0}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}, {0.2, 0.0},
};

// Coordinates for the roof (yellow)
GLfloat yellow[][2] = {
    {-0.5, 0.8}, {0.2, 0.8},
    {-0.5, 0.7}, {0.2, 0.7},
    {-0.5, 0.6}, {-0.4, 0.6}, {-0.3, 0.6}, {-0.2, 0.6}, {-0.1, 0.6}, {0.0, 0.6}, {0.1, 0.6}, {0.2, 0.6},
    {-0.5, 0.5}, {-0.4, 0.5}, {-0.3, 0.5}, {-0.2, 0.5}, {-0.1, 0.5}, {0.0, 0.5}, {0.1, 0.5}, {0.2, 0.5},
    {-0.6, 0.4}, {-0.5, 0.4}, {-0.3, 0.4}, {-0.2, 0.4}, {-0.1, 0.4}, {0.0, 0.4}, {0.2, 0.4}, {0.3, 0.4},
    {-0.6, 0.3}, {-0.5, 0.3}, {-0.3, 0.3}, {-0.2, 0.3}, {-0.1, 0.3}, {0.0, 0.3}, {0.2, 0.3}, {0.3, 0.3},
    {-0.6, 0.2}, {-0.5, 0.2}, {-0.4, 0.2}, {-0.3, 0.2}, {0.0, 0.2}, {0.1, 0.2}, {0.2, 0.2}, {0.3, 0.2},
    {-0.5, 0.1}, {-0.4, 0.1}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {0.2, 0.1},
};

// Color settings
GLfloat blackColor[] = { 0.0f, 0.0f, 0.0f };        // Black color
GLfloat yellowColor[] = { 1.0f, 1.0f, 0.0f };       // Yellow color
GLfloat backgroundColor[] = { 0.9f, 0.95f, 1.0f };  // Gentle light blue background

// Rotation and scaling variables
GLfloat angleX = 0.0, angleY = 0.0, scaleFactor = 1.0;
GLfloat transX = 0.0, transY = 0.0;
int lastX, lastY;
bool mousePressed = false;

// Rotation axis position
GLfloat rotationAxisX = 0.0, rotationAxisY = 0.0, rotationAxisZ = -1.0;

// Initial window size
int windowWidth = 800, windowHeight = 800;

// Display area range
GLfloat minX = -3, maxX = 3;  // Horizontal display range
GLfloat minY = -3, maxY = 3;  // Vertical display range

// Function to draw a cube
void drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat color[]) {
    // Set color
    glColor3fv(color);

    GLfloat halfSize = size / 2.0f;

    // Vertex array (each face has 4 vertices)
    GLfloat vertices[8][3] = {
        {x - halfSize, y - halfSize, z - halfSize},
        {x + halfSize, y - halfSize, z - halfSize},
        {x + halfSize, y + halfSize, z - halfSize},
        {x - halfSize, y + halfSize, z - halfSize},
        {x - halfSize, y - halfSize, z + halfSize},
        {x + halfSize, y - halfSize, z + halfSize},
        {x + halfSize, y + halfSize, z + halfSize},
        {x - halfSize, y + halfSize, z + halfSize}
    };

    // Define each face by the indices of its vertices
    GLuint faces[6][4] = {
        {0, 1, 2, 3}, // Front face
        {4, 5, 6, 7}, // Back face
        {1, 5, 6, 2}, // Right face
        {0, 4, 7, 3}, // Left face
        {3, 2, 6, 7}, // Top face
        {0, 1, 5, 4}  // Bottom face
    };

    // Draw each face
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();
}

// Initialization function
void init() {
    // Set background color
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set a fixed orthographic view, the graphic occupies a part of the window
    glOrtho(minX, maxX, minY, maxY, -5.0, 5.0);  // Use fixed range

    // Set modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Rendering function
void drawScene() {
    init();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
    glPointSize(15);  // Point size (if needed)

    glPushMatrix();

    // Apply translation and scaling
    glTranslatef(transX, transY, 0.0f);  // Translation
    glScalef(scaleFactor, scaleFactor, 1.0f);  // Scaling

    // Rotate around the specified axis
    glTranslatef(rotationAxisX, rotationAxisY, rotationAxisZ);  // Translate to rotation axis
    glRotatef(angleX, 1.0, 0.0, 0.0);  // Rotate around X-axis
    glRotatef(angleY, 0.0, 1.0, 0.0);  // Rotate around Y-axis
    glTranslatef(-rotationAxisX, -rotationAxisY, -rotationAxisZ); // Translate back

    // Draw black cubes
    for (int i = 0; i < sizeof(black) / sizeof(black[0]); i++) {
        drawCube(black[i][0], black[i][1], 0.0f, 0.1f, blackColor);
    }

    // Draw yellow cubes
    for (int i = 0; i < sizeof(yellow) / sizeof(yellow[0]); i++) {
        drawCube(yellow[i][0], yellow[i][1], 0.0f, 0.1f, yellowColor);
    }

    glPopMatrix();
    glutSwapBuffers(); // Use double buffering
}

// Mouse movement event handler
void mouseMotion(int x, int y) {
    if (mousePressed) {
        angleX += (y - lastY) * 0.5f;  // Rotate around Y-axis (up/down)
        angleY += (x - lastX) * 0.5f;  // Rotate around X-axis (left/right)
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

// Mouse button event handler, including mouse wheel
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mousePressed = true;
            lastX = x;
            lastY = y;
        }
        else {
            mousePressed = false;
        }
    }
    // Handle mouse wheel (only effective with freeGLUT)
    // Since mouse wheel might not work, we will use 'i' and 'k' for zoom
}

// Keyboard event handler
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        transY += 0.1f;  // Move up
        break;
    case 's':
        transY -= 0.1f;  // Move down
        break;
    case 'a':
        transX -= 0.1f;  // Move left
        break;
    case 'd':
        transX += 0.1f;  // Move right
        break;
    case 'i':
        scaleFactor *= 1.05f;  // Zoom in
        if (scaleFactor > 5.0f) scaleFactor = 5.0f; // Maximum zoom
        break;
    case 'k':
        scaleFactor /= 1.05f;  // Zoom out
        if (scaleFactor < 0.2f) scaleFactor = 0.2f; // Minimum zoom
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Window resize event handler
void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);  // Update viewport size
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use double buffering and depth buffer
    glutInitWindowSize(windowWidth, windowHeight);  // Set initial window size
    glutCreateWindow("Interactive 2D Visualization");
    glutDisplayFunc(drawScene);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);  // Listen for window size changes

    glutMainLoop();
    return 0;
}
