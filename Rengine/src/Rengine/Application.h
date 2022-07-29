#pragma once

#include "Core.h"

#include "Window.h"
#include "Rengine/LayerStack.h"
#include "Rengine/Events/Event.h"
#include "Rengine/Events/ApplicationEvent.h"

#include "Rengine/ImGui/ImGuiLayer.h"

#include "Rengine/Renderer/Shader.h"
#include "Rengine/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in the client
	Application* CreateApplication();
}
