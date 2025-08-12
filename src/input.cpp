#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "input.h"
#include "cube.h"

bool isDragging = false;
bool isRightClick = false;
int lastMouseX = 0, lastMouseY = 0;
float layerRotationAngle = 0.0f;

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        isDragging = true;
        lastMouseX = x;
        lastMouseY = y;
        
        if (button == GLUT_LEFT_BUTTON) {
            isRightClick = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            isRightClick = true;
        }
    } else if (state == GLUT_UP) {
        isDragging = false;
        isRightClick = false;
    }
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        int deltaX = lastMouseX - x;
        int deltaY = y - lastMouseY;
        
        if (isRightClick) {
            // Right-click drag: rotate entire cube
            cubeRotationY -= deltaX * 0.5f;  // Horizontal movement rotates around Y-axis (inverted for natural feel)
            cubeRotationX += deltaY * 0.5f;  // Vertical movement rotates around X-axis
            
            // Keep rotations in reasonable range
            if (cubeRotationX > 360.0f) cubeRotationX -= 360.0f;
            if (cubeRotationX < -360.0f) cubeRotationX += 360.0f;
            if (cubeRotationY > 360.0f) cubeRotationY -= 360.0f;
            if (cubeRotationY < -360.0f) cubeRotationY += 360.0f;
            
            std::cout << "Cube rotation: X=" << cubeRotationX << ", Y=" << cubeRotationY << std::endl;
        } else {
            // Left-click drag: rotate layer
            float dragDistance = sqrt(deltaX * deltaX + deltaY * deltaY);
            if (dragDistance > 5.0f) { // Minimum drag distance to start rotation
                
                // Determine which axis to rotate based on drag direction
                if (abs(deltaX) > abs(deltaY)) {
                    // Horizontal drag - rotate middle layer around Y-axis
                    float rotationAmount = deltaX * 2.0f;
                    rotateLayer(1, 0, rotationAmount);  // Y-axis, middle layer
                } else {
                    // Vertical drag - rotate middle layer around X-axis
                    float rotationAmount = deltaY * 2.0f;
                    rotateLayer(0, 0, rotationAmount);  // X-axis, middle layer
                }
            }
        }
        
        lastMouseX = x;
        lastMouseY = y;
        
        // Trigger a redraw
        glutPostRedisplay();
    }
}

void passiveMotion(int x, int y) {
}