#pragma once

#include <SDL.h>
#include <string>

class Renderer
{
    

public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Shutdown();
    void PresentCanvas(const class Canvas& canvas);
    bool CreateWindow(const std::string& title, int width, int height);

    friend class Canvas;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};
