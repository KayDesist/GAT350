#include "Framebuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"
#include "Color.h"
#include <SDL.h>

//setup
Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!m_texture) {
		std::cerr << "Error creating Texture: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}

//shape draws
void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	color_t& dest = m_buffer[x + (y * m_width)];
	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawPointClip(int x, int y, const color_t& color)
{
	if (x < 0 || x >= m_width)  return;
	if (y < 0 || y >= m_height) return;

	color_t& dest = m_buffer[x + (y * m_width)];
	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	//Maple's Way
	if (x + w < 0 || x >= m_width || y + h < 0 || y >= m_height) return;

	int x1 = std::max(x, 0);
	int x2 = std::min(x + w, m_width);
	int y1 = std::max(y, 0);
	int y2 = std::min(y + h, m_height);

	for (int sy = y1; sy < y2; sy++) {
		int index = x1 + sy * m_width;
		std::fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1), color);
	}

	// ** My way ** //
	//for (int i = 0; i < h; i++) {
	//	if (i + y >= m_height || i + y < 0) continue;
	//	for (int j = 0; j < w; j++) {
	//		if (j + x >= m_width || j + x < 0) continue;
	//
	//		//draw rect
	//		DrawPoint(x + j, y + i,color);
	//	}
	//}

}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	//y = mx + b

	int dx = x2 - x1; //run
	int dy = y2 - y1; //rise

	if (dx == 0) {
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y < y2; y++) {
			m_buffer[x1 + y * m_width] = color;
		}
	}
	else {
		float m = dy / (float)dx; // rise over run
		float b = y1 - (m * x1);

		if (std::abs(dx) > std::abs(dy)) {
			for (int x = x1; x <= x2; x++) {
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}
		}
		else {
			for (int y = y1; y < y2; y++) {
				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;
			}
		}
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	bool steep = (std::abs(dy) > std::abs(dx));
	if (steep) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	dx = x2 - x1;
	dy = std::abs(y2 - y1);

	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;


	int y = y1;
	for (int x = x1; x < x2; x++) {
		steep ? DrawPoint(y, x, color) : DrawPoint(x, y, color);
		error -= dy;
		if (error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	if (x1 > m_width || y1 > m_height) return;
	if (x2 > m_width || y2 > m_height) return;
	if (x3 > m_width || y3 > m_height) return;

	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawBresCircle(int xc, int yc, int x, int y, const color_t& color)
{
	//draws a point of the circle every 45 degrees 
	DrawPoint(xc + x, yc + y, color);
	DrawPoint(xc - x, yc + y, color);
	DrawPoint(xc + x, yc - y, color);
	DrawPoint(xc - x, yc - y, color);
	DrawPoint(xc + y, yc + x, color);
	DrawPoint(xc - y, yc + x, color);
	DrawPoint(xc + y, yc - x, color);
	DrawPoint(xc - y, yc - x, color);
}

void Framebuffer::DrawCircle(int xc, int yc, int radius, const color_t& color)
{
	int x = 0;
	int y = radius;
	int d = 3 - (2 * radius);
	//draws 0,45,90,135,180,225,270,315 points
	DrawBresCircle(xc, yc, x, y, color);

	//increases rotates the degrees being drawn
	//increases until x = radius
	while (y >= x) {
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else {
			d = d + (4 * x) + 6;
		}
		x++;

		DrawBresCircle(xc, yc, x, y, color);
	}
}

//curved lines
void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++) {
		int sx1 = Lerp(x1, x2, t1);
		int sy1 = Lerp(y1, y2, t1);

		float t2 = t1 + dt;

		int sx2 = Lerp(x1, x2, t2);
		int sy2 = Lerp(y1, y2, t2);

		t1 += dt;


		DrawLine(sx1, sy1, sx2, sy2, color);
	}

}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++) {

		int sx1, sy1;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t2, sx2, sy2);

		t1 += dt;
		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++) {

		int sx1, sy1;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t2, sx2, sy2);

		t1 += dt;
		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

//images
void Framebuffer::DrawImage(int x, int y, const Image& image)
{
	//check if off-screen
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
		return;
	}

	//iterate through image y
	for (int iy = 0; iy < image.m_height; iy++) {
		//set screen y
		int sy = y + iy;

		if (sy < 0 || sy >= m_height) {
			continue;
		}

		//iterate through image x

		for (int ix = 0; ix < image.m_width; ix++) {
			//set screen x
			int sx = x + ix;
			if (sx < 0 || sx >= m_width) {
				continue;
			}

			color_t color = image.m_buffer[ix + (iy * image.m_width)];

			if (color.a == 0) {
				continue;
			}
			DrawPoint(sx, sy, color);
		}
	}
}

//needs testing
void Framebuffer::CohenSutherLandClip(double x1, double y1, double x2, double y2)
{
	int code1 = ComputeCode(x1, y1);
	int code2 = ComputeCode(x2, y2);

	bool accept = false;

	while (true) {
		if (code1 == 0 && code2 == 0) {
			accept = true;
		}
		else if (code1 && code2) {
			break;
		}
		else {
			int code_out = 0;
			double x = 0;
			double y = 0;

			if (code1 != 0) {
				code_out = code1;
			}
			else {
				code_out = code2;
			}

			if (code_out && TOP) {
				x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
				y = y_max;
			}
			else if (code_out && BOTTOM) {
				x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
				y = y_min;
			}
			else if (code_out && RIGHT) {
				y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
				x = x_max;
			}
			else if (code_out && LEFT) {
				y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
				x = x_min;
			}

			if (code_out == code1) {
				x1 = x;
				y1 = y;
				code1 = ComputeCode(x1, y1);
			}
			else {
				x2 = x;
				y2 = y;
				code2 = ComputeCode(x2, y2);
			}
		}
	}
	if (accept) {
		std::cout << "Line accepted from " << x1 << ", " << y1 << " to " << x2 << ", " << y2 << std::endl;
	}
	else {
		std::cout << "nah" << std::endl;
	}
}

int Framebuffer::ComputeCode(double x, double y)
{
	int code = INSIDE;

	if (x < x_min) {
		code = LEFT;
	}
	else if (x > x_max) {
		code = RIGHT;
	}
	if (y < y_min) {
		code = BOTTOM;
	}
	else if (y > y_max) {
		code = TOP;
	}
	return code;
}