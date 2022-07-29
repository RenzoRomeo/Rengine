#pragma once

#include "Core.h"

#include "Window.h"
#include "Rengine/LayerStack.h"
#include "Rengine/Events/Event.h"
#include "Rengine/Events/ApplicationEvent.h"

#include "Rengine/ImGui/ImGuiLayer.h"

namespace Rengine
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in the client
	Application* CreateApplication();
}
