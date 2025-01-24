#pragma once
#include "Light.h"
#include <array>

struct vertex_t
{
	glm::vec3 position;
};

using vertexbuffer_t = std::vector<vertex_t>;

struct vertex_output_t
{
	glm::vec4 position;
	color3_t color;
};

class VertexShader
{
public:
	static void Process(const vertex_t& ivertex, vertex_output_t& overtex);

public:
	struct uniforms_t 
	{
		//
	};

	static uniforms_t uniforms;
};


