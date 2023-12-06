#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Random.h"
#include "Mesh.h"  // Add this line

#include <iostream>
#include <glm/gtx/color_space.hpp>
#include <vector>
#include "CornellBox.h"

// Function declarations for scene initialization
void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);  

int main(int, char**) {

    const int width = 1920 / 2;
    const int height = 1080 / 2;
    const int samples = 10;
    const int depth = 20;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", width, height);

    Canvas canvas(width, height, renderer);

    Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

    InitScene01(scene, canvas);
   InitScene02(scene, canvas);
    //InitScene03(scene, canvas);

    // Main rendering loop
    while (true) 
    {
        canvas.Clear({ 0, 0, 0, 1 });
        scene.Render(canvas, samples, depth);
        canvas.Update();
        renderer.PresentCanvas(canvas);

        // Handle events and input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return 0;
            }
        }
    }
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // create objects -> add to scene
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {
            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)    material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)    material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)    material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else                material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // Commented out the Lambertian plane
     auto plane = std::make_unique<Plane>(glm::vec3{ 0, -3, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
     scene.AddObject(std::move(plane));

    // Use Emissive material for the plane
     auto emissivePlane = std::make_unique<Plane>(glm::vec3{ 0, -8, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ static_cast<float>(random(0, 360)), 1.0f, 1.0f }), 5.0f));
     scene.AddObject(std::move(emissivePlane));

    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0.5f, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{0, 0.5f, 0}, glm::vec3{0, 45, 0});
    scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // Create CornellBox and add it to the scene
    CornellBox cornellBox(6.0f, 6.0f, 6.0f);
    cornellBox.AddToScene(scene);
}