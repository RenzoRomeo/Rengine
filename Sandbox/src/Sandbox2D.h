#pragma once

#include "Rengine.h"

class Sandbox2D : public Rengine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Rengine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Rengine::Event& e) override;
private:
	Rengine::OrthographicCameraController m_CameraController;

	// Temp
	Rengine::Ref<Rengine::VertexArray> m_SquareVA;
	Rengine::Ref<Rengine::Shader> m_FlatColorShader;
	Rengine::Ref<Rengine::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
