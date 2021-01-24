#include "Window.h"
#include "WindowsMessageMap.h"
#include <sstream>
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int		  nCmdShow) 
{
	try
	{
		Window wnd(640, 480, "Donkey Fart Box");
		//message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse Position:( " << e.GetPosX() << "," << e.GetPosY() << ")";
					wnd.SetTitle(oss.str());
				}
			}
		}
		if (gResult == -1)
		{
			return -1;
		}
		else//gResult == 0
		{
			return msg.wParam;
		}
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr,e.what(),e.GetType(),MB_OK|MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr,e.what(),"Standard Exceptions",MB_OK| MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr,"No details available","Unknown Exception",MB_OK|MB_ICONEXCLAMATION);
	}
	return -1;

}