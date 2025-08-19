#pragma once
#include <vector>
#include <deque>
#include "math.h"

namespace Cube {

struct Cubelet{
    // logical position indices in [-1,0,1]
    int i,j,k;
    Math::Mat4 T; // current transform
    Cubelet(int I,int J,int K);
};

struct Move{
    int axis;   // 0=x,1=y,2=z
    int layer;  // -1,0,1
    int dir;    // +1 or -1
    float progress; // degrees completed
    Move(int ax,int ly,int d);
};

extern std::vector<Cubelet> cubelets; // 27 cubelets
extern std::deque<Move> moveQueue;
extern std::vector<Move> undoStack;

void reset();
void enqueueMove(int axis,int layer,int dir);
bool inLayer(const Cubelet& c, int axis, int layer);
void rotateLayerStep(int axis,int layer,float angle);
void finalizeLayer(int axis,int layer,int dir);
void randomize(int moves);

} // namespace Cube
