#pragma once

#include "Rengine/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

namespace Rengine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}