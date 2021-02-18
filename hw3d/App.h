#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();

private:
	float temp_value_a = 0.0f;
	float temp_value_b = 0.0f;
	float temp_value_c = 20.0f;
	float speed_factor = 1.0f;
	ImguiManager imgui;
	Window wnd;
	ChiliTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	Camera cam;
	static constexpr size_t nDrawables = 180;
};