#include "repch.h"
#include "Shader.h"

#include "Rengine/Log.h"
#include "Rengine/Core.h"
#include "Rengine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rengine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}