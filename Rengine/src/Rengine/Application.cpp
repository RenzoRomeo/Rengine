#include "repch.h"
#include "Application.h"

#include "Rengine/Events/ApplicationEvent.h"
#include "Rengine/Log.h"

namespace Rengine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		RE_INFO(e);

		while (true);
	}
}