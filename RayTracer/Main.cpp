#include "Renderer/Renderer.h" 
#include <iostream> 
#include "Objects/Sphere.h"
#include "Objects/Scene.h"

using namespace std;

int main(int, char**)
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(600, 300);

	Canvas canvas(600, 300, renderer);
	Scene scene;

	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f, std::make_unique<Lambertian>(color3{ 1, 0, 0 })));
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, -100.5f, -1 }, 100.0f, std::make_unique<Lambertian>(color3{ 0.2f, 0.2f, 0.2f })));

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		//render scene
		canvas.Clear({ 0, 0, 0, 1 });
		renderer.Render(canvas, scene);

		/* for (int i = 0; i < 10000; i++) {
		//	canvas.DrawPoint({ random(0, 800), random(0, 600) }, { 1, 1, 1, 1 });
		}*/

		canvas.Update();

		renderer.CopyCanvas(canvas);
		renderer.Present();
	}
	renderer.Shutdown();
	return 0;
}