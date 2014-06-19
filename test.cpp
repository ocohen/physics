#include <SDL.h>
#include <iostream>
#include <cstring>
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
    bool quit = false;
    while (!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
        
        renderer.Clear();
        quit |= search->second->Tick(renderer);
        renderer.Flush();
        
        SDL_RenderPresent(displayRenderer);
    }
    
    SDL_Quit();
    
    
	return 1;
}