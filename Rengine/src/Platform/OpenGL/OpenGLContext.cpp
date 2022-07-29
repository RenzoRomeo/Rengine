#include "repch.h"
#include "OpenGLContext.h"

#include "Rengine/Log.h"

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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}