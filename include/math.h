#pragma once
#include <cmath>

namespace Math {

// Column-major like OpenGL
struct Mat4 {
    float m[16];
    static Mat4 identity(){
        Mat4 r;
        for(int i=0;i<16;++i) r.m[i]=(i%5==0)?1.f:0.f;
        return r;
    }
};

inline Mat4 mul(const Mat4&a,const Mat4&b){
    Mat4 r;
    for(int c=0;c<4;++c)
        for(int rI=0;rI<4;++rI){
            r.m[c*4+rI]=a.m[0*4+rI]*b.m[c*4+0]
                       +a.m[1*4+rI]*b.m[c*4+1]
                       +a.m[2*4+rI]*b.m[c*4+2]
                       +a.m[3*4+rI]*b.m[c*4+3];
        }
    return r;
}

inline Mat4 translate(float x,float y,float z){
    Mat4 r=Mat4::identity();
    r.m[12]=x; r.m[13]=y; r.m[14]=z;
    return r;
}

// axis: 0=x,1=y,2=z
inline Mat4 rotAxis(float angleDeg, int axis){
    float a=angleDeg*static_cast<float>(M_PI)/180.f, c=cosf(a), s=sinf(a);
    Mat4 r=Mat4::identity();
    if(axis==0){ r.m[5]=c; r.m[9]=-s; r.m[6]=s; r.m[10]=c; }
    else if(axis==1){ r.m[0]=c; r.m[8]=s; r.m[2]=-s; r.m[10]=c; }
    else { r.m[0]=c; r.m[4]=-s; r.m[1]=s; r.m[5]=c; }
    return r;
}

} // namespace Math
