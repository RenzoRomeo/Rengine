#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Rengine::VertexArray::Create();

	Rengine::Ref<Rengine::VertexBuffer> squareVB;
	Rengine::Ref<Rengine::IndexBuffer> squareIB;

	float squareVertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	squareVB = Rengine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{Rengine::ShaderDataType::Float3, "a_Position"},
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	squareIB = Rengine::IndexBuffer::Create(squareIndices, 6);
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Rengine::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Rengine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.8f, 0.2f, 0.3f, 1.0});

	Rengine::Renderer2D::EndScene();

	m_FlatColorShader->Bind();
	m_FlatColorShader->UploadUniformFloat4("u_Color", m_SquareColor);

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
