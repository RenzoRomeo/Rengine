#pragma once

#include "Rengine/Layer.h"

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
		float m_Time = 0.0f;
	};
}