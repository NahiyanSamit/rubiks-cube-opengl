// filepath: /rubiks-cube/rubiks-cube/src/input.h
#ifndef INPUT_H
#define INPUT_H

// External references to global rotation variables
extern float cubeRotationX, cubeRotationY;

// Mouse state variables
extern bool isDragging;
extern bool isRightClick;
extern int lastMouseX, lastMouseY;
extern float layerRotationAngle;

void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void passiveMotion(int x, int y);

#endif // INPUT_H