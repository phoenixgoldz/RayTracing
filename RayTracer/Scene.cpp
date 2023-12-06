#include "Scene.h"
#include "Random.h"
#include "MathUtils.h"
#include <iostream>
#include <iomanip>

Scene::Scene(const color3_t& topColor, const color3_t& bottomColor)
    : m_topColor(topColor), m_bottomColor(bottomColor) {}

void Scene::Render(Canvas& canvas, int numSamples, int depth)
{
    for (int y = 0; y < canvas.GetSize().y; y++)
    {
        for (int x = 0; x < canvas.GetSize().x; x++)
        {
            color3_t accumulatedColor{ 0, 0, 0 };

            // Perform multiple samples per pixel
            for (int s = 0; s < numSamples; ++s)
            {
                glm::vec2 pixel(static_cast<float>(x) + random01(), static_cast<float>(y) + random01());
                glm::vec2 point = pixel / glm::vec2(canvas.GetSize());
                point.y = 1.0f - point.y;

                ray_t ray = m_camera->GetRay(point);

                raycastHit_t raycastHit;
                accumulatedColor += Trace(ray, 0, 100, raycastHit, depth);
            }

            // Average the accumulated color over the samples
            accumulatedColor /= static_cast<float>(numSamples);

            canvas.DrawPoint(glm::vec2(x, y), color4_t(accumulatedColor, 1));
        }

        // Display render progress
        DisplayProgress(y, canvas.GetSize().y);
    }
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
    bool rayHit = false;
    float closestDistance = maxDistance;

    for (const auto& object : m_objects)
    {
        if (object->Hit(ray, minDistance, closestDistance, raycastHit))
        {
            rayHit = true;
            closestDistance = raycastHit.distance;
        }
    }

    // if ray hit object, scatter (bounce) ray and check for next hit
    if (rayHit)
    {
        ray_t scattered;
        color3_t color;

        // check if maximum depth (number of bounces) is reached, get color from material and scattered ray
        if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
        {
            // recursive function, call self and modulate (multiply) colors of depth bounces
            return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
        }
        else
        {
            // reached the maximum depth of bounces (color is black)
            return color3_t{ 0, 0, 0 };
        }
    }

    // if ray not hit, return scene sky color
    glm::vec3 direction = glm::normalize(ray.direction);
    float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
    color3_t color = lerp(m_bottomColor, m_topColor, t);

    return color;
}

void Scene::SetCamera(std::shared_ptr<Camera> camera)
{
    m_camera = camera;
}

void Scene::AddObject(std::unique_ptr<Object> object)
{
    m_objects.push_back(std::move(object));
}

void Scene::DisplayProgress(int currentRow, int totalRows) const
{
    // Display render progress
    std::cout << std::setprecision(2) << std::setw(5) << (static_cast<float>(currentRow) / totalRows) * 100 << "%\n";
}
