#pragma once

void initGL();
void initApp();

void display();
void reshape(int w,int h);
void update();

void mouseButton(int button,int state,int x,int y);
void mouseMotion(int x,int y);
void keyboard(unsigned char key,int x,int y);
