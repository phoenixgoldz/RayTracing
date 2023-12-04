#pragma once

#include "Object.h" 
#include <glm/glm.hpp>

class Sphere : public Object
{
public:
    Sphere() = default;
    Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material);

    bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
    glm::vec3 m_center{ 0.0f, 0.0f, 0.0f };
    float m_radius = 0.0f;
};
