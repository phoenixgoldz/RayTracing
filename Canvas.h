#pragma once
#include "Renderer.h" 
#include "Color.h"    

#include <..\SDL2-2.28.5\include\SDL.h>
#include <glm/glm.hpp>
#include <vector>


namespace nc {

	class Canvas
	{
	public:
		Canvas(int width, int height, const Renderer& renderer);
		~Canvas();

		void Update();

		void Clear(const color4_t& color);
		void DrawPoint(const glm::ivec2& point, const color4_t& color);

		const glm::ivec2& GetSize() const { return m_size; }

		friend class Renderer; // Allow Renderer to access Canvas private data

	private:
		SDL_Texture* m_texture = nullptr; // Forward declaration of SDL_Texture pointer
		std::vector<rgba_t> m_buffer;
		glm::ivec2 m_size = { 0 };
	};
}
