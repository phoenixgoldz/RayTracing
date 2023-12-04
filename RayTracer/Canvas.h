#pragma once

#include "Renderer.h"
#include "Color.h"

#include <glm/glm.hpp>
#include <vector>


class Canvas
{
public:
    Canvas(int width, int height, const Renderer& renderer);
    ~Canvas();

    void Update();

    void Clear(const color4_t& color);
    void DrawPoint(const glm::ivec2& point, const color4_t& color);

    const glm::ivec2& GetSize() const { return m_size; }

    friend class Renderer;

private:
    SDL_Texture* m_texture; // Forward declaration of SDL_Texture
    std::vector<rgba_t> m_buffer;
    glm::ivec2 m_size;
};
