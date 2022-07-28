#pragma once

#include "Rengine/Layer.h"
#include "Rengine/Events/MouseEvent.h"
#include "Rengine/Events/KeyEvent.h"
#include "Rengine/Events/ApplicationEvent.h"

namespace Rengine
{
	class RENGINE_API ImGuiLayer : public Rengine::Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}