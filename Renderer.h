#pragma once
#include <..\SDL2-2.28.5\include\SDL.h>

namespace nc {
    class Renderer {
    public:
        Renderer() : m_window(nullptr), m_renderer(nullptr) {}
        ~Renderer();

        void PresentCanvas(const Canvas& canvas);

        friend class Canvas; 


        bool Initialize();
        void Shutdown();
        bool CreateWindow();

    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
    };
}