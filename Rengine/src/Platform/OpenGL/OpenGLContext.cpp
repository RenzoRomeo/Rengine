#include "repch.h"
#include "OpenGLContext.h"

#include "Rengine/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rengine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		RE_CORE_ASSERT(windowHandle, "Window handle is NULL!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RE_CORE_ASSERT(status, "Failed to initialize Glad!");
	
		RE_CORE_INFO("OpenGL Info:");
		RE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		RE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		RE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}