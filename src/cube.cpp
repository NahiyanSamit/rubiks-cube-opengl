#include "cube.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Global rotation variables (for backward compatibility)
float cubeRotationX = 0.0f;
float cubeRotationY = 0.0f;

// Global cube instance
RubiksCube rubiksCube;

// Define standard Rubik's cube colors
Color colors[6] = {
    Color(1.0f, 1.0f, 1.0f),  // 0: White (front)
    Color(1.0f, 1.0f, 0.0f),  // 1: Yellow (back)
    Color(1.0f, 0.0f, 0.0f),  // 2: Red (right)
    Color(1.0f, 0.5f, 0.0f),  // 3: Orange (left)
    Color(0.0f, 1.0f, 0.0f),  // 4: Green (top)
    Color(0.0f, 0.0f, 1.0f)   // 5: Blue (bottom)
};

RubiksCube::RubiksCube() {
    globalRotX = 0.0f;
    globalRotY = 0.0f;
    globalRotZ = 0.0f;
    initializeCube();
}

void RubiksCube::initializeCube() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                Cubie& cube = cubes[x][y][z];
                
                // Set grid position (-1, 0, 1)
                cube.gridX = x - 1;
                cube.gridY = y - 1;
                cube.gridZ = z - 1;
                
                // Set initial position
                cube.posX = cube.gridX;
                cube.posY = cube.gridY;
                cube.posZ = cube.gridZ;
                
                // Initialize rotations
                cube.rotX = cube.rotY = cube.rotZ = 0.0f;
            }
        }
    }
}

void drawCubie(const Cubie& cube) {
    glPushMatrix();
    
    // Apply position
    glTranslatef(cube.posX, cube.posY, cube.posZ);
    
    // Apply rotations
    glRotatef(cube.rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(cube.rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(cube.rotZ, 0.0f, 0.0f, 1.0f);
    
    float size = 0.45f; // Half the cube size
    
    glBegin(GL_QUADS);
    
    // Front face (Z+)
    glColor3f(colors[0].r, colors[0].g, colors[0].b);
    glVertex3f(-size, -size,  size);
    glVertex3f( size, -size,  size);
    glVertex3f( size,  size,  size);
    glVertex3f(-size,  size,  size);
    
    // Back face (Z-)
    glColor3f(colors[1].r, colors[1].g, colors[1].b);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size,  size, -size);
    glVertex3f( size,  size, -size);
    glVertex3f( size, -size, -size);
    
    // Right face (X+)
    glColor3f(colors[2].r, colors[2].g, colors[2].b);
    glVertex3f( size, -size, -size);
    glVertex3f( size,  size, -size);
    glVertex3f( size,  size,  size);
    glVertex3f( size, -size,  size);
    
    // Left face (X-)
    glColor3f(colors[3].r, colors[3].g, colors[3].b);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size,  size);
    glVertex3f(-size,  size,  size);
    glVertex3f(-size,  size, -size);
    
    // Top face (Y+)
    glColor3f(colors[4].r, colors[4].g, colors[4].b);
    glVertex3f(-size,  size, -size);
    glVertex3f(-size,  size,  size);
    glVertex3f( size,  size,  size);
    glVertex3f( size,  size, -size);
    
    // Bottom face (Y-)
    glColor3f(colors[5].r, colors[5].g, colors[5].b);
    glVertex3f(-size, -size, -size);
    glVertex3f( size, -size, -size);
    glVertex3f( size, -size,  size);
    glVertex3f(-size, -size,  size);
    
    glEnd();
    
    // Draw black edges
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    
    // Bottom edges
    glVertex3f(-size, -size, -size); glVertex3f( size, -size, -size);
    glVertex3f( size, -size, -size); glVertex3f( size, -size,  size);
    glVertex3f( size, -size,  size); glVertex3f(-size, -size,  size);
    glVertex3f(-size, -size,  size); glVertex3f(-size, -size, -size);
    
    // Top edges
    glVertex3f(-size,  size, -size); glVertex3f( size,  size, -size);
    glVertex3f( size,  size, -size); glVertex3f( size,  size,  size);
    glVertex3f( size,  size,  size); glVertex3f(-size,  size,  size);
    glVertex3f(-size,  size,  size); glVertex3f(-size,  size, -size);
    
    // Vertical edges
    glVertex3f(-size, -size, -size); glVertex3f(-size,  size, -size);
    glVertex3f( size, -size, -size); glVertex3f( size,  size, -size);
    glVertex3f( size, -size,  size); glVertex3f( size,  size,  size);
    glVertex3f(-size, -size,  size); glVertex3f(-size,  size,  size);
    
    glEnd();
    
    glPopMatrix();
}

void RubiksCube::drawCube() {
    glPushMatrix();
    
    // Apply global rotations
    glRotatef(globalRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(globalRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(globalRotZ, 0.0f, 0.0f, 1.0f);
    
    // Draw all small cubes
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                drawCubie(cubes[x][y][z]);
            }
        }
    }
    
    glPopMatrix();
}

void RubiksCube::rotateLayer(int axis, int layer, float angle) {
    std::cout << "Rotating layer " << layer << " around axis " << axis << " by " << angle << " degrees" << std::endl;
    
    // Convert layer from (-1, 0, 1) to array index (0, 1, 2)
    int layerIndex = layer + 1;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Cubie* cube = nullptr;

            switch(axis) {
                case 0: // X-axis rotation (left/right faces)
                    cube = &cubes[layerIndex][i][j];
                    cube->rotX += angle;
                    break;
                case 1: // Y-axis rotation (top/bottom faces)
                    cube = &cubes[i][layerIndex][j];
                    cube->rotY += angle;
                    break;
                case 2: // Z-axis rotation (front/back faces)
                    cube = &cubes[i][j][layerIndex];
                    cube->rotZ += angle;
                    break;
            }
        }
    }
}

void RubiksCube::updateCubePositions() {
    // Update global rotations from the old variables (for compatibility)
    globalRotX = cubeRotationX;
    globalRotY = cubeRotationY;
}

// Wrapper functions for backward compatibility
void drawEntireCube() {
    rubiksCube.updateCubePositions();
    rubiksCube.drawCube();
}

void rotateLayer(int axis, int layer, float angle) {
    rubiksCube.rotateLayer(axis, layer, angle);
}