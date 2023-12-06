#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"  
#include "Random.h"

#include <iostream>
#include <glm/gtx/color_space.hpp>
#include <vector>

int main(int, char**) {
	
	const int width = 400;
	const int height = 400;
	const int samples = 1;
	const int depth = 2;

	Renderer renderer;

	// Create material with a specific max distance
	auto material = std::make_shared<Lambertian>(color3_t{ 1.2f });

	if (!renderer.Initialize() || !renderer.CreateWindow("My Window", 1920 / 2, 1080 / 2)) {
		std::cerr << "Failed to initialize renderer." << std::endl;
		return 1;
	}

	Canvas canvas(1920 / 2, 1080 / 2, renderer);

	// Create Camera
	float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 1 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	// Create Scene with depth
	Scene scene(20, glm::vec3{ 0.5f, 0.7f, 1.0f }, glm::vec3{ 1.0f,1.0f,1.0f });

	scene.SetCamera(camera);

	// Create spheres with random radius and materials in the scene
	for (int x = -10; x < 10; x++) {
		for (int z = -10; z < 5; z++) {

			// create random material
			float r = random01();
			std::shared_ptr<Material> material;

			if (r < 0.3f) {
				glm::vec3 randomColor = glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f });
				material = std::make_shared<Lambertian>(randomColor);
			}
			else if (r < 0.6f) {
				glm::vec3 metalColor{ random(0.5f, 1.0f) };
				float fuzziness = random(0, 0.5f);
				material = std::make_shared<Metal>(metalColor, fuzziness);
			}
			else if (r < 0.9f) {
				float refractionIndex = random(1.1f, 2);
				material = std::make_shared<Dielectric>(color3_t{ 1.0f }, refractionIndex);
			}
			else {
				glm::vec3 emissiveColor = glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f });
				float intensity = 5.0f;
				material = std::make_shared<Emissive>(emissiveColor, intensity);
			}

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	// Create a Plane
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));

	// Create a Triangle
	auto triangleMaterial = std::make_shared<Lambertian>(color3_t{ 2,2,2 });
	auto triangle = std::make_unique<Triangle>(glm::vec3{ 1, 0, -5 }, glm::vec3{ 0, 1, -5 }, glm::vec3{ -1, 0, -5 }, triangleMaterial);
	scene.AddObject(std::move(triangle));

	// Main rendering loop
	while (true) {
		// Render scene 
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas, 4);
		canvas.Update();
		renderer.PresentCanvas(canvas);

		// Handle events and input
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				// Exit the loop when the window is closed
				return 0;
			}
		}
	}
}


