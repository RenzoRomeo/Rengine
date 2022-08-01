#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Rengine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Rengine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Rengine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
	Rengine::RenderCommand::Clear();

	Rengine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Rengine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0});
	Rengine::Renderer2D::DrawQuad({ 0.5f, -1.0f }, { 0.5f, 0.75f }, {0.2f, 0.3f, 0.8f, 1.0});
	Rengine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

	Rengine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Rengine::Event& e)
{
	m_CameraController.OnEvent(e);
}
