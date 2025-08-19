#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include "app.h"
#include "cube.h"
#include "math.h"

namespace {

// rendering params
float cameraRotX=25.f, cameraRotY=-35.f; // whole-cube rotation
int lastMouseX=0,lastMouseY=0;
bool rightDown=false,leftDown=false;

// animation / timing
bool animate=true;
int lastFrameTime=0;

// colors: R, G, B, Y, O, W faces
const float FACE_COLORS[6][3]={
    {0.8f,0.0f,0.0f},{0.0f,0.6f,0.0f},{0.0f,0.2f,0.8f},
    {0.9f,0.9f,0.0f},{1.0f,0.5f,0.0f},{0.9f,0.9f,0.9f}
};

void applyMat(const Math::Mat4& M){ glMultMatrixf(M.m); }

void drawCubelet(){
    glBegin(GL_QUADS);
    // +X (R)
    glColor3fv(FACE_COLORS[0]); glNormal3f(1,0,0);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    // -X (O)
    glColor3fv(FACE_COLORS[4]); glNormal3f(-1,0,0);
    glVertex3f(-0.5f,-0.5f, -0.5f); glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
    // +Y (W)
    glColor3fv(FACE_COLORS[5]); glNormal3f(0,1,0);
    glVertex3f(-0.5f,0.5f,-0.5f); glVertex3f(-0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,-0.5f);
    // -Y (Y)
    glColor3fv(FACE_COLORS[3]); glNormal3f(0,-1,0);
    glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,0.5f); glVertex3f(-0.5f,-0.5f,0.5f);
    // +Z (B)
    glColor3fv(FACE_COLORS[2]); glNormal3f(0,0,1);
    glVertex3f(-0.5f,-0.5f,0.5f); glVertex3f(-0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,0.5f); glVertex3f(0.5f,-0.5f,0.5f);
    // -Z (G)
    glColor3fv(FACE_COLORS[1]); glNormal3f(0,0,-1);
    glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,-0.5f); glVertex3f(0.5f,0.5f,-0.5f); glVertex3f(-0.5f,0.5f,-0.5f);
    glEnd();

    // black borders
    glDisable(GL_LIGHTING);
    glLineWidth(20.0f);
    glColor3f(0,0,0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f,-0.5f, -0.5f); glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f,0.5f,-0.5f); glVertex3f(-0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,-0.5f);
    glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,0.5f); glVertex3f(-0.5f,-0.5f,0.5f);
    glVertex3f(-0.5f,-0.5f,0.5f); glVertex3f(-0.5f,0.5f,0.5f); glVertex3f(0.5f,0.5f,0.5f); glVertex3f(0.5f,-0.5f,0.5f);
    glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,-0.5f); glVertex3f(0.5f,0.5f,-0.5f); glVertex3f(-0.5f,0.5f,-0.5f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_LIGHTING);
}

void keyMove(unsigned char key){
    switch(key){
        case 'z': Cube::enqueueMove(0,-1,+1); break;
        case 'Z': Cube::enqueueMove(0,-1,-1); break;
        case 'x': Cube::enqueueMove(0, 0,+1); break;
        case 'X': Cube::enqueueMove(0, 0,-1); break;
        case 'c': Cube::enqueueMove(0, 1,+1); break;
        case 'C': Cube::enqueueMove(0, 1,-1); break;
        case 'v': Cube::enqueueMove(1, 1,+1); break;
        case 'V': Cube::enqueueMove(1, 1,-1); break;
        case 'b': Cube::enqueueMove(1, 0,+1); break;
        case 'B': Cube::enqueueMove(1, 0,-1); break;
        case 'n': Cube::enqueueMove(1,-1,+1); break;
        case 'N': Cube::enqueueMove(1,-1,-1); break;
        default: break;
    }
}

} // anon

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.08f,0.08f,0.1f,1);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    GLfloat globalAmb[4] = {0.25f,0.25f,0.25f,1.f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    GLfloat L0amb[4] = {0.35f,0.35f,0.35f,1.f};
    GLfloat L0dif[4] = {0.95f,0.95f,0.95f,1.f};
    GLfloat L0spec[4]= {0.20f,0.20f,0.20f,1.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT,  L0amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  L0dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, L0spec);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat Mspec[4] = {0.10f,0.10f,0.10f,1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Mspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 8.f);
}

void initApp(){
    lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-12);
    glRotatef(cameraRotX,1,0,0);
    glRotatef(cameraRotY,0,1,0);

    GLfloat pos0[4]={12.f,14.f,18.f,1.f};
    glLightfv(GL_LIGHT0,GL_POSITION,pos0);

    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0);
    GLfloat pos[4]={10,10,10,1}; glLightfv(GL_LIGHT0,GL_POSITION,pos);

    for(auto &c: Cube::cubelets){
        glPushMatrix();
        applyMat(c.T);
        drawCubelet();
        glPopMatrix();
    }

    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45.0,(double)w/h,0.1,100.0);
}

void update(){
    int now=glutGet(GLUT_ELAPSED_TIME);
    int dt = now - lastFrameTime; if(dt<=0) dt=1; lastFrameTime=now;

    if(animate && !Cube::moveQueue.empty()){
        Cube::Move &mv = Cube::moveQueue.front();
        float step = 360.f/2.f * (dt/1000.f); // ~180°/s
        float remaining = 90.f - mv.progress;
        float a = std::min(step, remaining) * mv.dir;
        Cube::rotateLayerStep(mv.axis, mv.layer, a);
        mv.progress += fabsf(a);
        if(mv.progress>=90.f-1e-3f){
            Cube::finalizeLayer(mv.axis,mv.layer,mv.dir);
            Cube::moveQueue.pop_front();
        }
    }

    glutPostRedisplay();
}

void mouseButton(int button,int state,int x,int y){
    if(button==GLUT_RIGHT_BUTTON) rightDown = (state==GLUT_DOWN);
    if(button==GLUT_LEFT_BUTTON)  leftDown  = (state==GLUT_DOWN);
    lastMouseX=x; lastMouseY=y;
}

void mouseMotion(int x,int y){
    int dx=x-lastMouseX, dy=y-lastMouseY; lastMouseX=x; lastMouseY=y;
    if(rightDown){
        cameraRotY += dx*0.3f; cameraRotX += dy*0.3f;
    } else if(leftDown){
        int w=glutGet(GLUT_WINDOW_WIDTH), h=glutGet(GLUT_WINDOW_HEIGHT);
        float ny = 2.f*(h-y)/h - 1.f; // top=+1 .. bottom=-1
        int layer = (ny>0.33f)? 1 : (ny<-0.33f? -1 : 0);
        if(std::abs(dx)>std::abs(dy)){
            Cube::enqueueMove(1, layer, dx>0? +1:-1);
        }else{
            Cube::enqueueMove(0, layer, dy>0? +1:-1);
        }
        leftDown=false;
    }
}

void keyboard(unsigned char key,int,int){
    switch(key){
        case 27: case 'q': case 'Q': std::exit(0); break;
        case 'W': case 'w': cameraRotX -= 5; break;
        case 'S': case 's': cameraRotX += 5; break;
        case 'A': case 'a': cameraRotY -= 5; break;
        case 'D': case 'd': cameraRotY += 5; break;
        case 'E': case 'e': animate=!animate; break;
        default: keyMove(key); break;
    }
}