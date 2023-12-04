#pragma once

#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>

// Seed the random number generator
inline void seedRandom(unsigned int seed)
{
    std::srand(seed);
}

// Generate a random float in the range [0, 1)
inline float random01()
{
    return static_cast<float>(std::rand()) / RAND_MAX;
}

// Generate a random float in the range [min, max)
inline float random(float min, float max)
{
    if (min > max)
        std::swap(min, max);

    return min + (max - min) * random01();
}

// Random vector function
inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
    return glm::vec3(
        random(min.x, max.x),
        random(min.y, max.y),
        random(min.z, max.z)
    );
}

// Random vector in a unit sphere function
inline glm::vec3 RandomInUnitSphere()
{
    return glm::normalize(glm::vec3(
        2.0f * random01() - 1.0f,
        2.0f * random01() - 1.0f,
        2.0f * random01() - 1.0f
    ));
}
