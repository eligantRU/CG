#include "stdafx.h"
#include "Window.h"
#include "consts.h"

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;
    glewInit();

    CWindow window;
    window.Show(WINDOW_SIZE);
    window.DoGameLoop();

	return 0;
}
