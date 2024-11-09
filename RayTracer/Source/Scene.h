#pragma once
#include "SceneObject.h"
#include <vector>
#include <memory>

class Scene {
public:
	Scene() = default;
	void Update();
	void AddObject(std::unique_ptr<class SceneObject> object) { m_objects.push_back(std::move(object)); }
	void Render(class Framebuffer& framebuffer, const class Camera& camera, int samples = 10, int depth = 5);

	void SetSky(const color3_t& skybottom, const color3_t& skytop) {
		m_skybot = skybottom;
		m_skytop = skytop;
	}

	friend class Tracer;

private:
	std::vector < std::unique_ptr<class SceneObject>> m_objects;
	color3_t m_skybot{ 1 };
	color3_t m_skytop{ .5f,.5f,.5f };
};