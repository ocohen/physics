#ifndef TINY_RENDERER_H
#define TINY_RENDERER_H
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

namespace TinyRenderer
{
class Renderer
{
public:
    Renderer(float inWidth, float inHeight);
    void SetBackground(const float * colour);
    void InitGL();
    void Clear();
    void DrawLine(const float * start, const float *end, const float * colour = 0, float thickness = 1.f);
    void DrawTriangle(const float * a, const float * b, const float * c, const float * colour = 0, float thickness = 1.f);
    void DrawSolidTriangle(const float * a, const float * b, const float * c, const float * colour);
    //tris is just an index buffer, but we treat it as triangles (num indices = numTris * 3)
    void DrawMesh(const float * vertices, const int * tris, int numTris, int stride=3, const float * colour = 0, bool solid=true, float thickness =1.f);
    void SetCameraPosition(const float * eye);
    void SetCameraLookAt(const float * eye, const float * target, const float * up);
    void SetCameraLense(float angleFOV);
    void SetDimensions(float width, float height);
    void Flush();
private:
    float width;
    float height;
    float mv[16];
    float projection[16];
};

inline Renderer::Renderer(float inWidth, float inHeight)
{
    InitGL();
    SetDimensions(inWidth, inHeight);
    
    float eye[3] = {0,0,0};
    float target[3] = {0,0,-1};
    float up[3] = {0,0,1};
    SetCameraLookAt(eye,target,up);
    SetCameraLense(90);
}

inline void Renderer::SetBackground(const float * colour)
{
    glClearColor(colour[0], colour[1], colour[2], 0.f);
}

inline void Renderer::InitGL()
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}

inline void Renderer::SetDimensions(float inWidth, float inHeight)
{
    width = inWidth;
    height = inHeight;
    
    glViewport(0, 0, width, height);
}

inline void Renderer::Clear()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

inline void Renderer::DrawLine(const float * start, const float * end, const float * colour, float thickness)
{
    glLineWidth(thickness);
    if(colour)
    {
           glColor3f(colour[0], colour[1], colour[2]);
    }else
    {
           glColor3f(1.f,1.f,1.f);
    }
    
    glBegin(GL_LINES);
    glVertex3f(start[0], start[1], start[2]);
    glVertex3f(end[0], end[1], end[2]);
    glEnd();
}

inline void Renderer::DrawTriangle(const float * a, const float * b, const float * c, const float * colour, float thickness)
{
    DrawLine(a,b,colour,thickness);
    DrawLine(b,c,colour,thickness);
    DrawLine(c,a,colour,thickness);
}

inline void Renderer::DrawSolidTriangle(const float * a, const float * b, const float * c, const float * colour)
{
    if(colour)
    {
           glColor3f(colour[0], colour[1], colour[2]);
    }else
    {
           glColor3f(1.f,1.f,1.f);
    }
    
    glBegin(GL_TRIANGLES);
    glVertex3f(a[0], a[1], a[2]);
    glVertex3f(b[0], b[1], b[2]);
    glVertex3f(c[0], c[1], c[2]);
    glEnd();
}

inline void Renderer::DrawMesh(const float * vertices, const int * tris, int numTris, int stride, const float * colour, bool solid, float thickness)
{
    for(int i=0; i<numTris; i++)
    {
        int a = tris[i*3];
        const float * vA = &vertices[a*stride];
        
        int b = tris[i*3+1];
        const float * vB = &vertices[b*stride];
        
        int c = tris[i*3+2];
        const float * vC = &vertices[c*stride];
        
        if(solid)
        {
            DrawSolidTriangle(vA,vB,vC,colour);            
        }else
        {
            DrawTriangle(vA,vB,vC,colour,thickness);
        }

    }
}

inline void Renderer::Flush()
{
    glFlush();
}

inline void CrossProduct(const float * a, const float * b, float * c)
{
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
}

inline float DotProduct(const float * a, const float * b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

inline void Normalize(const float * x, float * xn)
{
    float l = sqrt(DotProduct(x,x));
    xn[0] = x[0] / l;
    xn[1] = x[1] / l;
    xn[2] = x[2] / l;
}

inline void Renderer::SetCameraPosition(const float * eye)
{
    glMatrixMode( GL_MODELVIEW );
    glLoadMatrixf(mv);
    glTranslatef(-eye[0], -eye[1], -eye[2]);    
}


inline void Renderer::SetCameraLookAt(const float * eye, const float * target, const float * refUp)
{
    float side[3];
    float forward[3];
    float up[3];
    
    forward[0] = target[0] - eye[0];
    forward[1] = target[1] - eye[1];
    forward[2] = target[2] - eye[2];
    
    Normalize(forward, forward);
    Normalize(refUp, up);

    CrossProduct(forward,up, side); //compute side
    CrossProduct(side,forward,up);  //compute orthogonal up
    
    mv[0] = side[0];
    mv[1] = up[0];
    mv[2] = -forward[0];
    mv[3] = 0.f;

    mv[4] = side[1];
    mv[5] = up[1];
    mv[6] = -forward[1];
    mv[7] = 0.f;

    mv[8] = side[2];
    mv[9] = up[2];
    mv[10] = -forward[2];
    mv[11] = 0.f;

    mv[12] = 0;
    mv[13] = 0;
    mv[14] = 0;
    mv[15] = 1.f;
    
    glMatrixMode( GL_MODELVIEW );
    glLoadMatrixf(mv);
    glTranslatef(-eye[0], -eye[1], -eye[2]);
}

inline float anglesToRadians(float angle)
{
    return 3.14159 * angle / 180.f;
}

inline void Renderer::SetCameraLense(float angleFOV)
{
    const float near = 1.f;
    const float far = 100.f;
    const float ratio = (width > 0.f && height > 0.f) ? width / height : 1.f;
    const float size = tanf(anglesToRadians(angleFOV) / 2.f);
    
    float right = size;
    float top = size / ratio;
    
    projection[0] = near/right;
    projection[1] = 0.f;
    projection[2] = 0.f;
    projection[3] = 0.f;
        
    projection[4] = 0.f;
    projection[5] = near/top;
    projection[6] = 0.f;
    projection[7] = 0.f;
    
    projection[8] = 0.f;
    projection[9] = 0.f;
    projection[10] = -(far+near) / (far - near);
    projection[14] = -2.f*far*near / (far - near);
        
    projection[12] = 0.f;
    projection[13] = 0.f;
    projection[11] = -1.f;
    projection[15] = 0.f;
    
    glMatrixMode( GL_PROJECTION );
    glLoadMatrixf(projection);
}

}

#endif