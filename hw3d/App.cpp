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
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}