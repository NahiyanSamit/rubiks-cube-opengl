#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include "app.h"
#include "cube.h"

int main(int argc,char**argv){
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000,800);
    glutCreateWindow("Rubik's Cube (FreeGLUT/C++)");

    initGL();

    Cube::reset();
    initApp();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}