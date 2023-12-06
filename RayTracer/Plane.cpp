#include "Plane.h"
#include "MathUtils.h"

Plane::Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material)
    : Object(material), m_center(center), m_normal(glm::normalize(normal)) {}

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
    float denominator = glm::dot(ray.direction, m_normal);

    if (approximately(denominator, 0.0f)) {
        return false;  
    }

    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;

    if (t < minDistance || t > maxDistance) {
        return false;  
    }

    raycastHit.distance = t;
    raycastHit.point = ray.At(t);
    raycastHit.normal = m_normal;
    raycastHit.material = GetMaterial();

    return true;
}
