#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    Framebuffer framebuffer(*renderer,800, 600);

    Image image;
    image.Load("sillycat.png");


    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        // clear screen
        //SDL_SetRenderDrawColor(renderer->m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer->m_renderer);

        framebuffer.Clear(color_t{0,0,0,255});

        int x = rand() % framebuffer.m_width;
        int x2 = rand() % framebuffer.m_width;
        int x3 = rand() % framebuffer.m_width;
        int y = rand() % framebuffer.m_height;
        int y2 = rand() % framebuffer.m_height;
        int y3 = rand() % framebuffer.m_height;

        //for (int i = 0; i < 100; i++) {
        //    framebuffer.DrawPoint(x, y, color_t{ 255,255,255,255 });
        //}

        //framebuffer.DrawRect(750, 10, 100, 100, color_t{ 255,255,255,255 });
        
        //for (int i = 0; i < 100; i++) {
        //    framebuffer.DrawPoint(x-2,y+3,color_t{255,255,255,255});
        //    framebuffer.DrawPoint(x + 3,y,color_t{255,255,255,255});
        //    framebuffer.DrawPoint(x+4,y - 2,color_t{255,255,255,255});
        //    framebuffer.DrawPoint(x,y + 7,color_t{255,255,255,255});
        //    framebuffer.DrawPoint(x,y,color_t{255,255,255,255});
        //}
       
      

      int mx, my;
      SDL_GetMouseState(&mx, &my); 
    

      framebuffer.DrawLine(x, y, x2, y2, color_t{ 255,0,255,255 });
      //framebuffer.DrawTriangle(x, y, x2, y2,x3,y3, color_t{ 255,0,255,255 });
      //framebuffer.DrawCircle(x,y , 50, { 55,100,156,255 });
      framebuffer.DrawImage(-300, -200, image);

      //framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255,255,0,255 });
        //framebuffer.DrawQuadraticCurve(100, 200, 200, 100, 300, 200, { 255,0,0,255 });
      framebuffer.DrawCubicCurve(300, 500, 300, 200, mx, my, 600, 500, { 255,0,0,255 });



      framebuffer.Update();
      renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);

    }
    return 0;
} 

