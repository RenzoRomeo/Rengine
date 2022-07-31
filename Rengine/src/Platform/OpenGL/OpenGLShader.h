#pragma once

#include <string>
#include <unordered_map>

#include "Rengine/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Rengine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformInt(const std::string& name, int value) override;
		virtual void UploadUniformFloat(const std::string& name, float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		GLint GetUniformLocation(const std::string& name) const;
	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
	};
}