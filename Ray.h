#pragma once
#include <glm/glm.hpp>

struct ray_t
{
    ray_t() = default;
    ray_t(const glm::vec3& origin, const glm::vec3& direction) :
        origin(origin),
        direction(glm::normalize(direction))
    {}

    glm::vec3 GetPoint(float distance) const { return origin + distance * direction; }

    glm::vec3 origin;      // 3D origin
    glm::vec3 direction;   // 3D direction

    glm::vec3 operator*(float t) const { return origin + t * direction; }
};
