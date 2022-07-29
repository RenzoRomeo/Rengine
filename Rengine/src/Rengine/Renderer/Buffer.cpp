#include "repch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Rengine/Log.h"
#include "Rengine/Core.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Rengine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: RE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		RE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}