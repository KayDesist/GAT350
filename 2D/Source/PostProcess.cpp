#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm> 

//change color to c if it still continues to not work

	void PostProcesss::Invert(std::vector<color_t>& buffer)
	{ 
			std::for_each(buffer.begin(), buffer.end(), [](auto& color)
			{
				color.r = 255 - color.r;
				color.g = 255 - color.g;
				color.b = 255 - color.b;

			});
	}

	void PostProcesss::Monochrome(std::vector<color_t>& buffer)
	{
		std::for_each(buffer.begin(), buffer.end(), [](auto& color)
		{	
			unint8_t average = static_cast<unint8_t>((color.r + color.g + color.b)/ 3); 

			color.r = average;
			color.g = average;
			color.b = average;

		});

	}

	void PostProcesss::Brightness(std::vector<color_t>& buffer, int brightness)
	{ 
		std::for_each(buffer.begin(), buffer.end(), [](auto& color)
			{
				color.r= static_cast<unint8_t>(Clamp(color.r+brightness, 0, 255));
				color.g= static_cast<unint8_t>(Clamp(color.g+brightness, 0, 255));
				color.b= static_cast<unint8_t>(Clamp(color.b+brightness, 0, 255));

			});
	}
