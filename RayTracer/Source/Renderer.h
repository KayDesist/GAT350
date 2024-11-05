#pragma once
#include <SDL.h>
#include <iostream>

class Renderer {
public:
	bool Initialize();
	bool CreateWindow(int width, int height);
	void CopyFramebuffer(const class Framebuffer* framebuffer);

	SDL_Renderer* m_renderer = nullptr;
private:
	SDL_Window* m_window = nullptr;
	int m_width = 0;
	int m_height = 0;
};