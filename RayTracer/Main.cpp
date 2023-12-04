#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Random.h" 

#include <iostream>
#include <vector>

int main(int, char**) {
    Renderer renderer;

    // Create material with a specific max distance
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

    if (!renderer.Initialize() || !renderer.CreateWindow("My Window", 1920 / 2, 1080 / 2)) {
        std::cerr << "Failed to initialize renderer." << std::endl;
        return 1;
    }

    Canvas canvas(1920 / 2, 1080 / 2, renderer); // Adjusted canvas size

    // Create Camera
    float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

    // Create Scene with depth
    Scene scene(20, glm::vec3{ 0.5f, 0.7f, 1.0f }, glm::vec3{ 0.1f, 0.1f, 0.1f });

    scene.SetCamera(camera);

    // Add spheres to the scene using a loop
    std::vector<glm::vec3> spherePositions;
    int numSpheres = 20;

    for (int i = 0; i < numSpheres; ++i)
    {
        // Generate random positions for spheres
        float x = random(-20.0f, 20.0f);
        float y = random(-20.0f, 20.0f);
        float z = random(-20.0f, -2.0f); // Ensure spheres are placed in front of the camera
        glm::vec3 position(x, y, z);

        // Generate random radius for spheres
        float radius = random(0.5f, 2.0f);

        auto sphere = std::make_unique<Sphere>(position, radius, material);
        scene.AddObject(std::move(sphere));
    }

    // Main rendering loop
    while (true) {
        // Render scene 
        canvas.Clear({ 0, 0, 0, 1 });
        scene.Render(canvas, 50);
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