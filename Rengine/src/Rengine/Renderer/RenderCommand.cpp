#include "repch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rengine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}