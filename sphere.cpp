#include <vector>
#include <ctime>
#include <cstdlib>

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
        pts[0] = Vector3(25,0,25);

        return true;
    }
    
    bool Tick(TinyRenderer::Renderer & renderer, float seconds)
    {
        r += seconds;
        float target[] = {0,0,0};
        float up[] = {0,1,0};
        float position[] = {100*sin(r),0,100*cos(r)};
        float red[] = {1,0,0};
        renderer.SetCameraLookAt(position, target, up);
        
        for(int i=0; i<pts.size(); i++)
        {
            if(i == 0)
            {
                renderer.DrawPoint(&pts[i].x, red);
            }else
            {
                renderer.DrawPoint(&pts[i].x);
            }

        }
        

        
        return true;
    }
    
private:
    float r;
    std::vector<Vector3> pts;
};
TEST(BoundingSphere, "boundingsphere");