#pragma once

#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"

class CornellBox {
public:
    CornellBox(float width, float height, float depth);

    // Function to add Cornell Box objects to a scene
    void AddToScene(Scene& scene);

protected:
    float boxWidth;
    float boxHeight;
    float boxDepth;

    // Function to create walls of the Cornell Box
    void CreateWalls(Scene& scene);

    // Function to create spheres in the Cornell Box
    void CreateSpheres(Scene& scene);
};
