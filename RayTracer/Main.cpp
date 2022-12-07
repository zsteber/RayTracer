#include "Renderer/Renderer.h" 
#include <iostream> 
#include "Objects/Sphere.h"
#include "Objects/Scene.h"
#include "Renderer/Camera.h"

using namespace std;

int main(int, char**)
{

	const int width = 800;
	const int height = 600;
	const int samples = 10;


	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(width, height);

	Canvas canvas(width, height, renderer);
	Camera camera({ 0, 1, 2 }, { 0, 0, 0 }, { 0, 1, 0 }, 90.0f, width / (float)height);
	Scene scene;

	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f, std::make_unique<Lambertian>(color3{ 1, 0, 1 })));
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 1, 0, -1 }, 0.5f, std::make_unique<Metal>(color3{ 1, 1, 1 }, 0.1f)));
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
		renderer.Render(canvas, scene, camera, samples);

		canvas.Update();

		renderer.CopyCanvas(canvas);
		renderer.Present();
	}
	renderer.Shutdown();

	return 0;
}