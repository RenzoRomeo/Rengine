#pragma once

#include "Core.h"

#include "Window.h"
#include "Rengine/LayerStack.h"
#include "Rengine/Events/Event.h"
#include "Rengine/Events/ApplicationEvent.h"

namespace Rengine
{
	class RENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in the client
	Application* CreateApplication();
}
