#include "stdafx.h"
#include "Window.h"
#include "consts.h"

int main(int, char * [])
{
	CWindow window;
    window.Show(WINDOW_SIZE);
    window.DoGameLoop();

    return 0;
}
