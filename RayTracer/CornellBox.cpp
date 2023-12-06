#include "CornellBox.h"

CornellBox::CornellBox(float width, float height, float depth)
    : boxWidth(width), boxHeight(height), boxDepth(depth) {}

void CornellBox::AddToScene(Scene& scene) {
    CreateWalls(scene);
    CreateSpheres(scene);
}

void CornellBox::CreateWalls(Scene& scene) {
    auto material = std::make_shared<Lambertian>(color3_t{ 0.5f });

    auto leftWall = std::make_unique<Plane>(glm::vec3{ -boxWidth / 2, 0, 0 }, glm::vec3{ 1, 0, 0 }, material);
    auto rightWall = std::make_unique<Plane>(glm::vec3{ boxWidth / 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, material);
    auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, -boxDepth / 2 }, glm::vec3{ 0, 0, 1 }, material);
    auto floor = std::make_unique<Plane>(glm::vec3{ 0, -boxHeight / 2, 0 }, glm::vec3{ 0, 1, 0 }, material);
    auto ceiling = std::make_unique<Plane>(glm::vec3{ 0, boxHeight / 2, 0 }, glm::vec3{ 0, -1, 0 }, material);

    scene.AddObject(std::move(leftWall));
    scene.AddObject(std::move(rightWall));
    scene.AddObject(std::move(backWall));
    scene.AddObject(std::move(floor));
    scene.AddObject(std::move(ceiling));
}

void CornellBox::CreateSpheres(Scene& scene) {
    auto redSphere = std::make_unique<Sphere>(glm::vec3{ -1, -boxHeight / 2 + 1, -2 }, 1.0f, std::make_shared<Lambertian>(color3_t{ 0.8f, 0.1f, 0.1f }));
    auto greenSphere = std::make_unique<Sphere>(glm::vec3{ 1, -boxHeight / 2 + 1, -2 }, 1.0f, std::make_shared<Lambertian>(color3_t{ 0.1f, 0.8f, 0.1f }));
    auto lightSphere = std::make_unique<Sphere>(glm::vec3{ 0, boxHeight / 2 - 1, -2 }, 1.0f, std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 4.0f));

    scene.AddObject(std::move(redSphere));
    scene.AddObject(std::move(greenSphere));
    scene.AddObject(std::move(lightSphere));
}
