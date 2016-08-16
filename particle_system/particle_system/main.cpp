#include "stdafx.h"
#include "consts.h"
#include "Window.h"

int main(int, char * [])
{
    CWindow window;
    window.Show(WINDOW_SIZE);
    window.DoGameLoop();

	return 0;
}
