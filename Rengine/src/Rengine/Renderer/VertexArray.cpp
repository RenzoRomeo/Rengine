#include "repch.h"
#include "VertexArray.h"

#include "Rengine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rengine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}