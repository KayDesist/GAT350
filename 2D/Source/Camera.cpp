#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
	m_view = glm::lookAt(eye,center,up);
}

void Camera::Setprojection(float fov,float aspect,float near, float far)
{
	m_projection = glm::perspective(glm::radians(fov),aspect,near,far);
}

glm::vec3 Camera::ModelToView(const glm::vec3& position) const
{
	return m_view * glm::vec4{ position,1 };
}

glm::vec3 Camera::ViewToProjection(const glm::vec3& position) const
{
	return m_projection * glm::vec4{ position,1 };
}

glm::vec2 Camera::ToScreen(const glm::vec3& position) const
{
	glm::vec4 clip = m_projection * glm::vec4{ position,1 };
	glm::vec3 ndc = clip / clip.w;	

	float x = (ndc.x + 1) * (m_width * 0.5f);
	float y = (ndc.y + 1) * (m_height * 0.5f);

	return glm::vec2(x,y);
}
