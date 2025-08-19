#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "cube.h"

namespace {
int irand(int a,int b){ return a + std::rand()%((b-a)+1); }
}

namespace Cube {

std::vector<Cubelet> cubelets;
std::deque<Move> moveQueue;

Cubelet::Cubelet(int I,int J,int K)
    : i(I), j(J), k(K),
      T(Math::mul(Math::translate(static_cast<float>(I),
                                  static_cast<float>(J),
                                  static_cast<float>(K)),
                  Math::Mat4::identity())){}

Move::Move(int ax,int ly,int d):axis(ax),layer(ly),dir(d),progress(0.f){}

void reset(){
    cubelets.clear();
    for(int i=-1;i<=1;++i)
        for(int j=-1;j<=1;++j)
            for(int k=-1;k<=1;++k)
                cubelets.emplace_back(i,j,k);
    moveQueue.clear();
}

void enqueueMove(int axis,int layer,int dir){
    moveQueue.emplace_back(axis,layer,dir);
}

bool inLayer(const Cubelet& c, int axis, int layer){
    float x = c.T.m[12];
    float y = c.T.m[13];
    float z = c.T.m[14];
    int rx = static_cast<int>(roundf(x));
    int ry = static_cast<int>(roundf(y));
    int rz = static_cast<int>(roundf(z));
    if(axis==0) return rx==layer;
    if(axis==1) return ry==layer;
    return rz==layer;
}

void rotateLayerStep(int axis,int layer,float angle){
    Math::Mat4 R = Math::rotAxis(angle, axis);
    Math::Mat4 C = Math::translate((axis==0?static_cast<float>(layer):0.f),
                                   (axis==1?static_cast<float>(layer):0.f),
                                   (axis==2?static_cast<float>(layer):0.f));
    Math::Mat4 Ci = Math::translate(-(axis==0?static_cast<float>(layer):0.f),
                                    -(axis==1?static_cast<float>(layer):0.f),
                                    -(axis==2?static_cast<float>(layer):0.f));
    for(auto &c: cubelets){
        if(inLayer(c,axis,layer))
            c.T = Math::mul(C, Math::mul(R, Math::mul(Ci, c.T)));
    }
}

void finalizeLayer(int axis,int layer,int /*dir*/){
    for(auto &c: cubelets){
        if(!inLayer(c,axis,layer)) continue;
        c.T.m[12]=roundf(c.T.m[12]);
        c.T.m[13]=roundf(c.T.m[13]);
        c.T.m[14]=roundf(c.T.m[14]);
        for(int i=0;i<16;++i){
            if(fabsf(c.T.m[i])<1e-4f) c.T.m[i]=0.f;
        }
    }
}

} // namespace Cube