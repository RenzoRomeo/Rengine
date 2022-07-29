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
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}