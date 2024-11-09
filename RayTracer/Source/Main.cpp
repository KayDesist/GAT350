#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include "Color.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Tracer.h"
#include "Model.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <iostream>
#include "Random.h"
#include "Triangle.h"

//void InitScene(Scene& scene);
//void InitScene01(Scene& scene, Camera& camera); 
void InitCornell(Scene& scene, Camera& camera);

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	Time time;
	Input input;
	bool quit = false;

	Renderer* renderer = new Renderer;
	renderer->Initialize();
	renderer->CreateWindow("Ray Tracer", 800, 600);
	Framebuffer framebuffer(*renderer, renderer->GetWidth(), renderer->GetHeight());

	Camera camera{ 70.0f,framebuffer.m_width / (float)framebuffer.m_height };
	camera.SetView({ 0,0,-5.0f }, { 0,0,0 });

	SetBlendMode(BlendMode::Normal);


	Scene scene;
	//InitScene01(scene, camera); 
	InitCornell(scene, camera);
	scene.Update();


	framebuffer.Clear(ColorConvert(color4_t{ 128,128,128,255 }));
	scene.Render(framebuffer, camera, 200, 10);
	//tracer.Render(framebuffer, camera);

	while (!quit)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}



		renderer->CopyFramebuffer(framebuffer);
		framebuffer.Update();

		SDL_RenderPresent(renderer->m_renderer);

	}




	return 0;
}



void InitScene(Scene& scene)
{
	std::shared_ptr<Material> material = std::make_unique<Lambertian>(color3_t{ 1,0,1 });
	std::shared_ptr<Material> planematerial = std::make_unique<Lambertian>(color3_t{ 0.5f,1,0.5f });
	std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> purple = std::make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.33f);
	std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 255, 255, 255 });
	std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 1, 0.5f, 0 }, 1.34);
	
	std::vector<std::shared_ptr<Material>> materials = { red, blue };


	auto model = std::make_unique<Model>(Transform{ glm::vec3{0, 0, 0 }, glm::vec3{0,20, 0},glm::vec3{ 1} }, material);
	model->Load("teapot.obj");
	scene.AddObject(std::move(model));

	/*One light source in the center of a white ceiling
		A green right wall
		A red left wall
		A white back wall
		A white floor*/
	std::unique_ptr<Sphere> object = std::make_unique<Sphere>(glm::vec3{ 0 }, 2.0f, red);


	auto WhitePlaneFloor = std::make_unique<Plane>(Transform{ glm::vec3{0,-5,-5} }, white);
	auto WhitePlaneBackWall = std::make_unique<Plane>(Transform{ glm::vec3{5,5,5}, glm::vec3 {100} }, white);
	auto RedPlaneLeft = std::make_unique<Plane>(Transform{ glm::vec3{-5,5,0}, glm::vec3{100} }, red);
	auto BluePlaneRight = std::make_unique<Plane>(Transform{ glm::vec3{0,-2,0},glm::vec3{0,0,20},glm::vec3{1,1,1} }, blue);
	auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 2, 0 }, glm::vec3{ 2, 0, 0 }, material);
	scene.AddObject(std::move(triangle));
	scene.AddObject(std::move(object));
	scene.AddObject(std::move(WhitePlaneFloor));
	scene.AddObject(std::move(WhitePlaneBackWall));
	scene.AddObject(std::move(RedPlaneLeft));


	// Function to select a random material from the vector
	auto getRandomMaterial = [&materials]() -> std::shared_ptr<Material> {int index = static_cast<int>(randomf(0, materials.size())); return materials[index]; };

	for (int i = 0; i < 10; ++i) {
		glm::vec3 random_position = random(glm::vec3{ -10.0f, -10.0f, -10.0f }, glm::vec3{ 10.0f, 10.0f, 10.0f });
		float random_radius = randomf(0.5f, 2.0f);  // Random radius between 0.5 and 2.0
		auto random_material = getRandomMaterial(); // Get a random material


		//auto sphere = std::make_unique<Sphere>(random_position, random_radius, random_material);
		//scene.AddObject(std::move(sphere));
	}


}

void InitScene01(Scene& scene, Camera& camera)
{
	camera.SetFOV(60.0f);
	camera.SetView({ 15, 5, 5 }, { 0, 0, 0 });

	camera.SetFOV(20.0f);
	camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
	auto green_material = std::make_shared<Lambertian>(color3_t(0, 0, 1));
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

	/*std::shared_ptr<Material> mat = std::make_shared<Lambertian>(color3_t{ 0.5f,0.5f,0.5f });
	auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0} }, mat);
	scene.AddObject(std::move(plane));*/


	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randomf();
			glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

			if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					sphere_material = std::make_shared<Lambertian>(albedo);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					auto fuzz = randomf(0.0f, 0.5f);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
			}
		}
	}
}	 

void InitCornell(Scene& scene, Camera& camera) {
	//camera
	camera.SetFOV(80.0f);
	camera.SetView({ 13, 2, 0 }, { 0, 0, 0 });

	//floor
	auto ground_material = std::make_shared<Lambertian>(color3_t(0.75f));
	auto green_material = std::make_shared<Lambertian>(color3_t(0, 1, 0));
	auto red_material = std::make_shared<Lambertian>(color3_t(1, 0, 0));
	auto roof_material = std::make_shared<Emissive>(color3_t(0.9f), 15.0f);
	auto sphere_material = std::make_shared<Dielectric>(color3_t(.5f), 1.33f);
	auto sphere_material2 = std::make_shared<Metal>(color3_t(.7f, .3f, .5f), 1.33f);

	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0,-30,0 } }, ground_material));
	//walls
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{0,0,-40},glm::vec3{90,0,0} }, red_material)); // left wall
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{0,0,40},glm::vec3{-90,0,0} }, green_material)); // right wall

	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ -75,0,0 },glm::vec3{0,0,-90} }, ground_material));

	//roof
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{0,40,0},glm::vec3{0,0,8},glm::vec3{-1} }, ground_material));

	//light
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{0,9,0},glm::vec3{0} }, 4.3f, roof_material));

	//sphere
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{0} }, 2.0f, sphere_material));
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{2,-1,-6} }, 3.0f, sphere_material2)); 


}