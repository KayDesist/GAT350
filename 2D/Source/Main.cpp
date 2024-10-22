#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[])
{
#pragma region Initialize

    Time time;

    Renderer* renderer = new Renderer;
    renderer->Initialize();
    renderer->CreateWindow(800, 600);

    Framebuffer framebuffer(*renderer, 800, 600);
    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0,0,-5 }, glm::vec3{ 0 });
    camera.Setprojection(90.0f, 800.0f / 600.0f, 0.1f, 200.0f);
    Transform cameraTransform{ {0,0,-50} };
    cameraTransform.rotation = { 90,90,90 };

    Input input;
    input.Initialize();
#pragma endregion
#pragma region Image_Init
    Image image;
    image.Load("sillycat.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    //imageAlpha.Load("cursed.png");
    SetBlendMode(BlendMode::Normal);
#pragma endregion
#pragma region Model_Init
    //vertices_t vertices = { {-5,5,0},{5,5,0},{-5,-5,0} };
    //Model model(vertices, { 255,0,0,255 });
    //Transform transform{ {0,0,0},{0,0,15},{2,2,2} };
#pragma endregion

    Model model;
    model.Load("teapot.obj");
    //model.Load("skull.obj");
    //model.Load("cube-2.obj");

    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();
#pragma region SDL_EVENT
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
#pragma endregion
        // clear screen
        framebuffer.Clear(color_t{ 128,128,128,255 });



#pragma region PostProcess
        //mouse input
        //int mx, my;
        //SDL_GetMouseState(&mx, &my);
        //SetBlendMode(BlendMode::Multiply);
        //framebuffer.DrawImage(10, 10, image);

        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer,50,30,20);
        //PostProcess::Brightness(framebuffer.m_buffer, 50);
        //PostProcess::Threshold(framebuffer.m_buffer, 125);
        //PostProcess::Noise(framebuffer.m_buffer, 15);
        //PostProcess::Posterization(framebuffer.m_buffer, 50);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //SetBlendMode(BlendMode::Alpha);
        //framebuffer.DrawImage(mx, my, imageAlpha);

        //PostProcess::Brightness(framebuffer.m_buffer, -125);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height,1);
#pragma endregion
#pragma region Triangle_move
        glm::vec3 direction{ 0 };
        if (input.GetKeyDown(SDL_SCANCODE_D)) { direction.x = 1; }
        if (input.GetKeyDown(SDL_SCANCODE_A)) { direction.x = -1; }
        if (input.GetKeyDown(SDL_SCANCODE_W)) { direction.y = -1; }
        if (input.GetKeyDown(SDL_SCANCODE_S)) { direction.y = 1; }
        if (input.GetKeyDown(SDL_SCANCODE_K)) { direction.z = -1; }
        if (input.GetKeyDown(SDL_SCANCODE_L)) { direction.z = 1; }

        cameraTransform.rotation.y = input.GetMousePosition().x * 0.1;

        cameraTransform.position += direction * 70.0f * time.GetDeltaTime();
        //camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());
        camera.SetView(cameraTransform.position, cameraTransform.position + glm::vec3{ 0,0,1 });

        model.DrawModel(framebuffer, camera, { 255,0,0,255 });

        //transform.rotation.z += 90 * time.GetDeltaTime();
        //transform.rotation.y += 90 * time.GetDeltaTime();
        //transform.rotation.x += 90 * time.GetDeltaTime();
        //model.Draw(framebuffer,transform.GetMatrix(),camera);
#pragma endregion


        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}