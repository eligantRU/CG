#include "stdafx.h"
#include "consts.h"
#include "Window.h"

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
