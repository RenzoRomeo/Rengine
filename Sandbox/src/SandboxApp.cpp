#include <Rengine.h>

#include "imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Rengine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquareColor(0.8f, 0.2f, 0.3f, 1.0f)
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

		m_Shader = Rengine::Shader::Create(vertexSource, fragmentSource);


		m_SquareVA.reset(Rengine::VertexArray::Create());

		std::shared_ptr<Rengine::VertexBuffer> m_SquareVB;
		std::shared_ptr<Rengine::IndexBuffer> m_SquareIB;

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_SquareVB.reset(Rengine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareVB->SetLayout({
			{Rengine::ShaderDataType::Float3, "a_Position"},
			{Rengine::ShaderDataType::Float2, "a_TexCoord"}
			});
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

		m_SquareShader = Rengine::Shader::Create(squareVertexSource, squareFragmentSource);

		std::string textureVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 v_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader = Rengine::Shader::Create(textureVertexSource, textureFragmentSource);

		m_Texture = Rengine::Texture2D::Create("assets/textures/Checkerboard.png");

		m_Texture->Bind();
		m_TextureShader->Bind();
		m_TextureShader->UploadUniformInt("u_Texture", 0);
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

		Rengine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Rengine::Renderer::Submit(m_Shader, m_VertexArray);

		Rengine::Renderer::EndScene();
	}

	void OnEvent(Rengine::Event& event) override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	Rengine::Ref<Rengine::Shader> m_Shader, m_TextureShader;
	Rengine::Ref<Rengine::VertexArray> m_VertexArray;

	Rengine::Ref<Rengine::Texture2D> m_Texture;
	Rengine::Ref<Rengine::Shader> m_SquareShader;
	Rengine::Ref<Rengine::VertexArray> m_SquareVA;
	glm::vec4 m_SquareColor;

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
	Rengine::WindowProps props("Sandbox, 600, 600");

	return new Sandbox();
}