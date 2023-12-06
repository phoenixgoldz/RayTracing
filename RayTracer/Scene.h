#pragma once

#include "Ray.h"
#include "Object.h"
#include "Color.h"
#include "Camera.h"
#include "Canvas.h"
#include <vector>

class Scene
{
public:
    Scene() = default;
    Scene(const color3_t& topColor, const color3_t& bottomColor);

    void Render(Canvas& canvas, int numSamples, int depth);

    color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);

    void SetCamera(std::shared_ptr<Camera> camera);
    void AddObject(std::unique_ptr<Object> object);

protected:
    std::shared_ptr<Camera> m_camera;
    std::vector<std::unique_ptr<Object>> m_objects;
    color3_t m_topColor;
    color3_t m_bottomColor;

private:
    void DisplayProgress(int currentRow, int totalRows) const;
};