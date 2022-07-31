#include "repch.h"
#include "Shader.h"

#include "Rengine/Log.h"
#include "Rengine/Core.h"
#include "Rengine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rengine
{
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}