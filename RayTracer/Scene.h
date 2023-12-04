#pragma once

#include "Ray.h"
#include "Object.h"
#include "Color.h"
#include "Camera.h"
#include "Canvas.h"

#include <memory>
#include <vector>

class Scene
{
public:
    Scene(int depth = 5) : m_depth{ depth } {}
    Scene(int depth, const color3_t& topColor, const color3_t& bottomColor) :
        m_depth{ depth },
        m_topColor{ topColor },
        m_bottomColor{ bottomColor }
    {}

    void Render(Canvas& canvas, int numSamples);

    color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);

    void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

    void AddObject(std::unique_ptr<Object> object)
    {
        m_objects.push_back(std::move(object));
    }

private:
    std::shared_ptr<Camera> m_camera;

    std::vector<std::unique_ptr<Object>> m_objects;

    int m_depth{ 5 };
    color3_t m_topColor{ 1.0f };
    color3_t m_bottomColor{ 0.5f };
};

