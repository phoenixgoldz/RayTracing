#pragma once
#include <glm/glm.hpp>

// Alias for color (RGB) with floating point values (0.0-1.0)
using color3_t = glm::vec3;

// Alias for color (RGBA) with floating point values (0.0-1.0)
using color4_t = glm::vec4;

// Alias for color (RGBA) with integer values
using rgba_t = uint32_t;

// Convert integer (8888) color representation to floating point (0.0-1.0) color representation
inline color4_t RGBAToColor(const rgba_t& rgba)
{
    float red = static_cast<float>((rgba >> 24) & 0xFF) / 255.0f;
    float green = static_cast<float>((rgba >> 16) & 0xFF) / 255.0f;
    float blue = static_cast<float>((rgba >> 8) & 0xFF) / 255.0f;
    float alpha = static_cast<float>(rgba & 0xFF) / 255.0f;

    return color4_t(red, green, blue, alpha);
}

// Convert floating point (0.0-1.0) color representation to integer (8888) color representation
inline rgba_t ColorToRGBA(const color4_t& color)
{
    uint8_t red = static_cast<uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255);
    uint8_t green = static_cast<uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255);
    uint8_t blue = static_cast<uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255);
    uint8_t alpha = static_cast<uint8_t>(glm::clamp(color.a, 0.0f, 1.0f) * 255);

    return (static_cast<uint32_t>(red) << 24) | (static_cast<uint32_t>(green) << 16) |
        (static_cast<uint32_t>(blue) << 8) | static_cast<uint32_t>(alpha);
}
