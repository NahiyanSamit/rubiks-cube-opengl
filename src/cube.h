// filepath: /rubiks-cube/rubiks-cube/src/cube.h
#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>

struct Color {
    float r, g, b;
    Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f) : r(red), g(green), b(blue) {}
};

struct Cubie {
    float posX, posY, posZ;  // Current position in 3D space
    int gridX, gridY, gridZ; // Original grid position (-1, 0, 1)

    Cubie() : posX(0), posY(0), posZ(0), gridX(0), gridY(0), gridZ(0) {}
};

struct RubiksCube {
    Cubie cubes[3][3][3];  // 3x3x3 array of small cubes
    float globalRotX, globalRotY, globalRotZ;  // Global rotation of entire cube
    
    RubiksCube();
    void initializeCube();
    void drawCube();
    void rotateLayer(int axis, int layer, float angle);
    void updateCubePositions();
};

// Global cube instance
extern RubiksCube rubiksCube;

// Define standard Rubik's cube colors
extern Color colors[6];

// Function declarations
void drawCubie(const Cubie& cube);
void initializeColors();
void drawEntireCube();
void drawCube(float x, float y, float z, int cubeX, int cubeY, int cubeZ); // Legacy function

#endif // CUBE_H