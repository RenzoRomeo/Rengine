#include "repch.h"
#include "VertexArray.h"

#include "Rengine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rengine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}