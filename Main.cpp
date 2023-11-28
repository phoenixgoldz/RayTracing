#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

#include <iostream>


int main()
{
    nc::Renderer renderer(400, 300);
    nc::Canvas canvas(400, 300, renderer);

    while (true)
    {
        canvas.Clear({ 0, 0, 0, 1 });

        for (int i = 0; i < 1000; i++)
        {
            glm::ivec2 point = { random(0, 399), random(0, 299) };
            color4_t color = { random01(), random01(), random01(), 1 };
            canvas.DrawPoint(point, color);
        }

        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    return 0;
}

