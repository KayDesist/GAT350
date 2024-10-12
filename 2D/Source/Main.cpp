#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h" 
#include "PostProcess.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    Framebuffer framebuffer(*renderer,800, 600);

    Image image;
    image.Load("scenic.jpg");


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
        
      //framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255,255,0,255 });
        //framebuffer.DrawQuadraticCurve(100, 200, 200, 100, 300, 200, { 255,0,0,255 });
        //framebuffer.DrawCubicCurve(300, 500, 300, 200, mx, my, 600, 500, { 255,0,0,255 });
        
      framebuffer.DrawImage(100, 100, image);


        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::Brightness(framebuffer.m_buffer,100);
        PostProcess::Posterize(framebuffer.m_buffer, 6);
        //PostProcess::Noise(framebuffer.m_buffer, 80);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
        //PostProcess::Threshold(framebuffer.m_buffer, 150);

        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 10);
      //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);


      framebuffer.Update();
      renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);

    }
    return 0;
} 

