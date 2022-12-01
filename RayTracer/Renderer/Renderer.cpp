#include "Renderer.h" 
#include <iostream> 

using namespace std;

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
	m_window = SDL_CreateWindow("2D Renderer", 100, 100, width, height, SDL_WINDOW_SHOWN);
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