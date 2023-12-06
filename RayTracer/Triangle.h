#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
    Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, std::shared_ptr<Material> material);

    bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& hit) override;

private:
    glm::vec3 m_v1;
    glm::vec3 m_v2;
    glm::vec3 m_v3;
};
