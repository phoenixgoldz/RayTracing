#pragma once

#include "Ray.h"
#include "Material.h"

class Emissive : public Material
{
public:
    Emissive(const glm::vec3& albedo, float intensity = 1.0f) : m_albedo(albedo), m_intensity(intensity) {}

    bool Scatter(const Ray& ray, const RaycastHit& raycastHit, glm::vec3& color, Ray& scattered) const override { return false; }
    glm::vec3 GetEmissive() const override { return m_albedo * m_intensity; }

private:
    glm::vec3 m_albedo{ 1, 1, 1 };
    float m_intensity{ 1 };
};