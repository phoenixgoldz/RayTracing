#include "Renderer.h"
#include <iostream>


int main(int argc, char** argv) {
	std::cout << "Hello world!\n";

	nc::Renderer renderer;
	if (!renderer.Initialize() || !renderer.CreateWindow()) {
		return 1;
	}

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}

