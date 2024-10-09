#pragma once
#include "FrameBuffer.h" 

namespace PostProcesss
{
	void Invert(std::vector<color_t>& buffer);
	void Monochrome(std::vector<color_t>& buffer); 
	void Brightness(std::vector<color_t>& buffer, int brightness); 
	
}