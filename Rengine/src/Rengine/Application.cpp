#include "repch.h"
#include "Application.h"

#include "Rengine/Events/ApplicationEvent.h"
#include "Rengine/Log.h"

namespace Rengine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}