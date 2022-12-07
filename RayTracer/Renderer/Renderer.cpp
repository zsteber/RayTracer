#include "Renderer.h" 
#include "../Objects/Scene.h"
#include <iostream> 

using namespace std;

void Renderer::Render(Canvas& canvas, Scene& scene, Camera& camera, int samples)
{
	// camera / viewport 
	glm::vec3 lowerLeft{ -2, -1, -1 };
	glm::vec3 eye{ 0, 0, 0 };
	glm::vec3 right{ 4, 0, 0 };
	glm::vec3 up{ 0, 2, 0 };

	for (int y = 0; y < canvas.GetHeight(); y++)
	{
		for (int x = 0; x < canvas.GetWidth(); x++)
		{

			color3 color{ 0, 0, 0 };
			for (int s = 0; s < samples; s++)
			{

				// get normalized (0 - 1) u, v coordinates from screen x and y 
				float u = x / (float)canvas.GetWidth();
				float v = 1 - (y / (float)canvas.GetHeight());
				// add random value (0-1) to screen x and y for anti-aliasing  
				glm::vec2 point = glm::vec2{ random01() + x, random01() + y } / glm::vec2{ canvas.m_width, canvas.m_height };

				// flip y 
				point.y = 1.0f - point.y;

				// create ray from camera 
				Ray ray = camera.PointToRay(point);

				// cast ray into scene 
				RaycastHit raycastHit;
				// add trace color value to color 
				color += scene.Trace(ray, 0.001f, 1000.0f, raycastHit, 5);
			}
			color /= samples;
			canvas.DrawPoint({ x, y }, color4(color, 1));
		}
	}
}

color3 Renderer::GetBackgroundFromRay(const Ray& ray)
{
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = 0.5f * (direction.y + 1.0f);

	return lerp(color3{ 1.0f }, color3{ 0.5f, 0.7f, 1.0f }, t);
}

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	if (m_window) SDL_DestroyWindow(m_window);
	if (m_renderer) SDL_DestroyRenderer(m_renderer);

	SDL_Quit();
}

bool Renderer::CreateWindow(int width, int height)
{
	m_window = SDL_CreateWindow("Ray Tracer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		cout << "SDL Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		cout << "SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

void Renderer::CopyCanvas(const Canvas& canvas)
{
	SDL_RenderCopy(m_renderer, canvas.m_texture, nullptr, nullptr);
}

void Renderer::Present()
{
	SDL_RenderPresent(m_renderer);
}
