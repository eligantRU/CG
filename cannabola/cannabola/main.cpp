#include "stdafx.h"

#include "WindowClient.h"
#include <SDL.h>

int main(int, char * [])
{
	try
	{
		CWindow window;
		window.Show("Cannabola", { 600, 600 });
		CWindowClient client(window);
		window.DoMainLoop();
	}
	catch (const std::out_of_range & ex)
	{
		const char * title = "Fatal Error";
		const char * message = ex.what();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
	}
	return 0;
}
