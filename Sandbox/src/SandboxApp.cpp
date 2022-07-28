#include <Rengine.h>

class ExampleLayer : public Rengine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		RE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rengine::Event& event) override
	{
		RE_TRACE("{0}", event);
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