#include "stdafx.h"
#include "Window.h"

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;
    glewInit();

    CWindow window;
    window.Show({1000, 800});
    window.DoGameLoop();

	return 0;
}
