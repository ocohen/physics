#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "vector3.h"
#include "matrix33.h"
#include "test.h"

float getRand()
{
    return (rand() % 1000) / 1000.f;
}

class BoundingSphere : public Test
{
public:
    bool Init()
    {
        r = 0;
        const int n = 100;
        pts.reserve(n);
        float left = -50;
        float right = 50;
        float up = -50;
        float down = 50;
        float front = -50;
        float back = 50;
        
        std::srand(std::time(0));
        
        for(int i=0; i<n; i++)
        {
            float x,y,z;
            x = getRand() * (right-left) + left;
            y = getRand() * (down-up) + up;
            z = getRand() * (back-front) + front;
            pts.push_back(Vector3(x,y,z));
        }
        
        //geometric mean (one of the worst ways)
        ComputeAverageSphere(averageCenter, averageRadius);        
        ComputeRitterSphere(ritterCenter, ritterRadius);
        
        std::cout << "Average:" << averageRadius<< std::endl;
        std::cout << "Ritter:" << ritterRadius<< std::endl;        
        

        return true;
    }
    
    bool Tick(TinyRenderer::Renderer & renderer, float seconds)
    {
        r += seconds;
        float target[] = {0,0,0};
        float up[] = {0,1,0};
        float position[] = {125*sin(r),0,125*cos(r)};

        renderer.SetCameraLookAt(position, target, up);
        
        for(int i=0; i<pts.size(); i++)
        {
            renderer.DrawPoint(&pts[i].x);
        }
        
        float red[] = {1,0,0};
        float green[] = {0,1,0};
        float blue[] = {0,0,1};
        
        renderer.DrawSphere(&averageCenter.x, averageRadius, 32, red);
        renderer.DrawSphere(&ritterCenter.x, ritterRadius, 32, green);
        
        renderer.DrawLine(&pts[ti].x, &pts[ti2].x, blue);
        
        return true;
    }    
    
    
private:
    float r;
    std::vector<Vector3> pts;
    Vector3 averageCenter;
    float averageRadius;
    
    Vector3 ritterCenter;
    float ritterRadius;
    
        
    void ComputeAverageSphere(Vector3 & center, float & radius)
    {
        center = Vector3::Zero;
        for(int i=0; i<pts.size(); i++)
        {
            center += pts[i];
        } 
        center *= 1.f / pts.size();
        
        float maxD = -1;
        for(int i=0; i<pts.size(); i++)
        {
            float d = (pts[i]-center).Length();
            maxD = d > maxD ? d : maxD;
        }
        
        radius = maxD;
    }
    
    float Min3(float a, float b, float c)
    {
        float minAb = a < b ? a : b;
        return  minAb < c ? minAb : c;
    }
    
    float Max3(float a, float b, float c)
    {
        float maxAb = a > b ? a : b;
        return  maxAb > c ? maxAb : c;
    }
    
    void GetMinMaxAABB(Vector3 & outMin, Vector3 & outMax)
    {
        int minx = 0; int miny = 0; int minz = 0;
        int maxx = 0; int maxy = 0; int maxz = 0;
        
        for(int i=1; i<pts.size(); i++)
        {
            if(pts[i].x < pts[minx].x) minx = i;
            if(pts[i].y < pts[miny].y) miny = i;
            if(pts[i].z < pts[minz].z) minz = i;

            if(pts[i].x > pts[maxx].x) maxx = i;
            if(pts[i].y > pts[maxy].y) maxy = i;
            if(pts[i].z > pts[maxz].z) maxz = i;
        }
        
        std::cout << minx << " " << maxx << std::endl;
        
        float xd2 = (pts[minx] - pts[maxx]).Length2();
        float yd2 = (pts[miny] - pts[maxy]).Length2();
        float zd2 = (pts[minz] - pts[maxz]).Length2();

        outMin = pts[minx];
        outMax = pts[maxx];
        if(yd2 > xd2 && yd2 > zd2)
        {
            outMin = pts[miny];
            outMax = pts[maxy];
        }else if(zd2 > xd2 && zd2 > yd2)
        {
            outMin = pts[minz];
            outMax = pts[maxz];
        }
    }
    
    void ComputeRitterSphere(Vector3 & outCenter, float & outRadius)
    {
        Vector3 min;
        Vector3 max;
        GetMinMaxAABB(min,max);
        
        Vector3 center = (min + max) * 0.5f;
        float radius = (max-min).Length() * 0.5f;
        float r2 = radius * radius;
        
        for(int i=0; i<pts.size(); i++)
        {
            Vector3 dir = (pts[i] - center);
            float d2 = dir.Length2();
            
            if(d2 > r2)
            {
                float d = sqrt(d2);
                float newRadius = (radius + d) * 0.5f;
                float k = (newRadius - radius) / d;
                radius = newRadius;
                r2 = radius * radius;
                center += dir * k;
            }
        }
        
        outCenter = center;
        outRadius = radius;
    }
    
    int ti;
    int ti2;
    
};
TEST(BoundingSphere, "boundingsphere");