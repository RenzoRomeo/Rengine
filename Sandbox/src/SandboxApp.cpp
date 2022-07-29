#include <Rengine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Rengine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello");
		ImGui::End();
	}

	void OnUpdate() override
	{
		if (Rengine::Input::IsKeyPressed(RE_KEY_TAB))
			RE_TRACE("TAB");
	}

	void OnEvent(Rengine::Event& event) override
	{
		// RE_TRACE("{0}", event);
	}
};

class Sandbox : public Rengine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Rengine::Application* Rengine::CreateApplication()
{
	return new Sandbox();
}