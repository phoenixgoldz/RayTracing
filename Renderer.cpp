#include <iostream>
#include "Renderer.h"

namespace nc{

    bool Renderer::Initialize() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    void Renderer::Shutdown() {
        if (m_renderer != nullptr) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
        if (m_window != nullptr) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
        SDL_Quit();
    }

    bool Renderer::CreateWindow() {
        m_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (!m_window) {
            std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!m_renderer) {
            std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        return true;
    }
}