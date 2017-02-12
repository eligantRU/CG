#include "stdafx.h"

#include "WindowClient.h"
#include <SDL.h>

int main(int, char * [])
{
	try
	{
		CWindow window;
		window.Show("Labyrinth", { 1000, 1000 });
		CWindowClient client(window);
		window.DoMainLoop();
	}
	catch (const std::exception & ex)
	{
		const char * title = "Fatal Error";
		const char * message = ex.what();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
	}
	return 0;
}
