#pragma once
#include <SDL.h>
#include <vector>
#include "Color.h"


class Framebuffer
{
public:
	Framebuffer(const class Renderer& renderer, int width, int height);
	~Framebuffer();

	void Update();
	void Clear(const color_t& color);

	void DrawPoint(int x, int y, const color_t& color);
	void DrawPointClip(int x, int y, const color_t& color);

	void DrawRect(int x, int y, int w, int h, const color_t& color);
	void DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawLine(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawCircle(int xc, int yc, int radius, const color_t& color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color);

	void DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color);
	void DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color);

	void DrawImage(int x, int y, const class Image& image);

	std::vector<color_t>& GetBuffer() { return m_buffer; };

private:
	void DrawBresCircle(int xc, int yc, int x, int y, const color_t& color);
	void CohenSutherLandClip(double x1, double y1, double x2, double y2); // still need to write
	int ComputeCode(double x, double y);



public:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_pitch{ 0 };

	SDL_Texture* m_texture{ nullptr };
	std::vector<color_t> m_buffer;

private:
	const int INSIDE = 0;
	const int LEFT = 1;
	const int RIGHT = 2;
	const int BOTTOM = 4;
	const int TOP = 8;

	const int x_max = 800;
	const int y_max = 600;
	const int x_min = 0;
	const int y_min = 0;
};