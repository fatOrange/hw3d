#include "App.h"
#include "Box.h"
#include "Melon.h"
#include "Pyramid.h"
#include "triangle_cube.h"
#include "SkinBox.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include "ChiliMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "Sheet.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd(800, 600, "The Donkey Fart Box")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()() {
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<TrangleCube>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<SkinBox>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 2:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			case 3:
				return std::make_unique<Sheet>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,3 }; //ѡ������
	};

	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);


	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));//Builds a left-handed perspective projection matrix. ��ͷ
	//wnd.Gfx().SetCamera(dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f));// ���ң����£���ǳ
}



int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

App::~App()
{}

void App::DoFrame()
{
	wnd.Gfx().SetCamera(cam.GetMatrix());

	const auto dt = timer.Mark() * speed_factor;

	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	for (auto& d : drawables)
	{
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}

	static char buffer[1024];

	// imgui window to control simulation speed
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("temp_value_a", &temp_value_a, -40.0f, 40.0f);
		ImGui::SliderFloat("temp_value_b", &temp_value_b, -40.0f, 40.0f);
		ImGui::SliderFloat("temp_value_c", &temp_value_c, -40.0f, 40.0f);
		ImGui::SliderFloat("Speed Factor", &speed_factor, -4.0f, 10.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::InputText("Butts", buffer, sizeof(buffer));
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
	}
	ImGui::End();
	// imgui window to control camera
	cam.SpawnControlWindow();

	// present
	wnd.Gfx().EndFrame();
}