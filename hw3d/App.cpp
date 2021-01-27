#include "App.h"
#include <sstream>
#include <iomanip>
App::App()
	:
	wnd(800, 600, "The Donkey Fart Box")
{}

int App::Go()
{
	MSG msg;
	BOOL gResult;
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}

	// check if GetMessage call itself borked
	if (gResult == -1)
	{
		throw CHWND_LAST_EXCEPT();
	}

	// wParam here is the value passed to PostQuitMessage
	return msg.wParam;
}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0);
	wnd.Gfx().DrawTestTriangle(
		timer.Peek(),
		wnd.mouse.GetPosX() / 400.f - 1.0f,
		-wnd.mouse.GetPosY() /300.f +1.0f
		);
	wnd.Gfx().EndFrame();
}