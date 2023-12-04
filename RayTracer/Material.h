#pragma once

#include "Ray.h"
#include "Random.h"
#include "Color.h"
#include "MathUtils.h"

class Material {
public:
    virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const color3_t& albedo) : albedo_(albedo) {}

    bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;

private:
    color3_t CalculateGradientColor(float distance) const;

private:
    float maxDistance_ = 100.0f;
    color3_t albedo_;
};

class Metal : public Material {
public:
    Metal(const color3_t& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz } {}

    bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override;

protected:
    glm::vec3 m_albedo{ 0 };
    float m_fuzz = 0;
};