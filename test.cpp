#include <SDL.h>
#include <iostream>
#include <ctime>
#include "test.h"
#include "tinyrenderer.h"

int main(int argc, const char ** argv)
{
	if(argc <= 1)
	{
		std::cout << "./a.out <test>" << std::endl;
		return 1;
	}
    
    TestMap * testMap = Test::GetTestMap();
    std::string key(argv[1]);
    
    TestMap::iterator search = testMap->find(key);
    if(search == testMap->end())
    {
    	std::cout << "couldn't find (" << argv[1] << ") in commands:" << std::endl;
        for(TestMap::iterator itr = testMap->begin(); itr != testMap->end(); ++itr)
        {
            std::cout << " " << itr->first << std::endl;
        }
        
        return 1;
    }
    
    if(search->second->Init() == false)
    {
        return 0;
    }
    
    SDL_Window* displayWindow;
    SDL_Renderer* displayRenderer;
    SDL_RendererInfo displayRendererInfo;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &displayWindow, &displayRenderer);
    SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
    
    TinyRenderer::Renderer renderer(800,600);

    SDL_Event event;    
    bool run = true;
    const double fps = 60.f;
    const float delta = 1.f/fps;
    double timeBank = delta;
    clock_t start,end;
    start = clock();
    
    while (run)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = false;
            }
        }
                
        end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        timeBank += seconds;
        start = end;
        
        if(timeBank >= delta)
        {
            while(timeBank >= delta)
            {
                timeBank -= delta;
                renderer.Clear();
                run &= search->second->Tick(renderer, (float)delta);
                renderer.Flush();
            }
            SDL_RenderPresent(displayRenderer);
            SDL_Delay(delta);
        }
    }
    
    SDL_Quit();
    
    
	return 1;
}