#include <Rengine.h>
#include <Rengine/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Rengine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_SquareColor(0.8f, 0.2f, 0.3f, 1.0f), m_CameraController(16.0f / 9.0f)
	{
		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexArray = Rengine::VertexArray::Create();

		std::shared_ptr<Rengine::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Rengine::IndexBuffer> m_IndexBuffer;

		m_VertexBuffer = Rengine::VertexBuffer::Create(vertices, sizeof(vertices));
		Rengine::BufferLayout layout = {
			{ Rengine::ShaderDataType::Float3, "a_Position" },
			{ Rengine::ShaderDataType::Float4, "a_Color" },
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer = Rengine::IndexBuffer::Create(indices, 3);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_SquareVA = Rengine::VertexArray::Create();

		std::shared_ptr<Rengine::VertexBuffer> m_SquareVB;
		std::shared_ptr<Rengine::IndexBuffer> m_SquareIB;

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_SquareVB = Rengine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		m_SquareVB->SetLayout({
			{Rengine::ShaderDataType::Float3, "a_Position"},
			{Rengine::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(m_SquareVB);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		m_SquareIB = Rengine::IndexBuffer::Create(squareIndices, 6);
		m_SquareVA->SetIndexBuffer(m_SquareIB);

		std::string squareVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_SquareShader = Rengine::Shader::Create("square", squareVertexSource, squareFragmentSource);

		auto textureShader = m_Shaders.Load("Texture", "assets/shaders/Texture.glsl");

		m_Texture = Rengine::Texture2D::Create("assets/textures/Checkerboard.png");

		m_Texture->Bind();
		textureShader->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Rengine::Timestep ts) override
	{
		// Updates
		m_CameraController.OnUpdate(ts);

		// Rendering
		Rengine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.1f});
		Rengine::RenderCommand::Clear();

		Rengine::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				m_SquareShader->UploadUniformFloat4("u_Color", m_SquareColor);
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rengine::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_Shaders.Get("Texture");

		Rengine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Rengine::Renderer::EndScene();
	}

	void OnEvent(Rengine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	Rengine::ShaderLibrary m_Shaders;
	Rengine::Ref<Rengine::VertexArray> m_VertexArray;

	Rengine::Ref<Rengine::Texture2D> m_Texture;
	Rengine::Ref<Rengine::Shader> m_SquareShader;
	Rengine::Ref<Rengine::VertexArray> m_SquareVA;
	glm::vec4 m_SquareColor;

	Rengine::OrthographicCameraController m_CameraController;
};

class Sandbox : public Rengine::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Rengine::Application* Rengine::CreateApplication()
{
	Rengine::WindowProps props("Sandbox, 600, 600");

	return new Sandbox();
}