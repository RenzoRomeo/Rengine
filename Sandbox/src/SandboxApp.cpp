#include <Rengine.h>

#include "imgui/imgui.h"

#include <glm/glm.hpp>

class ExampleLayer : public Rengine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexArray.reset(Rengine::VertexArray::Create());

		std::shared_ptr<Rengine::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Rengine::IndexBuffer> m_IndexBuffer;

		m_VertexBuffer.reset(Rengine::VertexBuffer::Create(vertices, sizeof(vertices)));
		Rengine::BufferLayout layout = {
			{ Rengine::ShaderDataType::Float3, "a_Position" },
			{ Rengine::ShaderDataType::Float4, "a_Color" },
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(Rengine::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Rengine::Shader::Create(vertexSource, fragmentSource));


		m_SquareVA.reset(Rengine::VertexArray::Create());

		std::shared_ptr<Rengine::VertexBuffer> m_SquareVB;
		std::shared_ptr<Rengine::IndexBuffer> m_SquareIB;

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		m_SquareVB.reset(Rengine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareVB->SetLayout({ {Rengine::ShaderDataType::Float3, "a_Position"} });
		m_SquareVA->AddVertexBuffer(m_SquareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		m_SquareIB.reset(Rengine::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(m_SquareIB);

		std::string squareVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			
			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_SquareShader.reset(Rengine::Shader::Create(squareVertexSource, squareFragmentSource));
	}

	void OnImGuiRender() override
	{

	}

	void OnUpdate(Rengine::Timestep ts) override
	{
		RE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Rengine::Input::IsKeyPressed(RE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Rengine::Input::IsKeyPressed(RE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Rengine::Input::IsKeyPressed(RE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Rengine::Input::IsKeyPressed(RE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Rengine::Input::IsKeyPressed(RE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Rengine::Input::IsKeyPressed(RE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Rengine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		Rengine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rengine::Renderer::BeginScene(m_Camera);

		Rengine::Renderer::Submit(m_SquareShader, m_SquareVA);
		Rengine::Renderer::Submit(m_Shader, m_VertexArray);

		Rengine::Renderer::EndScene();
	}

	void OnEvent(Rengine::Event& event) override
	{

	}

private:
	std::shared_ptr<Rengine::Shader> m_Shader;
	std::shared_ptr<Rengine::VertexArray> m_VertexArray;

	std::shared_ptr<Rengine::Shader> m_SquareShader;
	std::shared_ptr<Rengine::VertexArray> m_SquareVA;

	Rengine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Rengine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Rengine::Application* Rengine::CreateApplication()
{
	return new Sandbox();
}