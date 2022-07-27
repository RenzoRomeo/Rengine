#include <Rengine.h>

class Sandbox : public Rengine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Rengine::Application* Rengine::CreateApplication()
{
	return new Sandbox();
}