#pragma once

#include "Rengine/Core/Application.h"
#include "Rengine/Core/Log.h"

#ifdef RE_PLATFORM_WINDOWS

extern Rengine::Application* Rengine::CreateApplication();

int main(int argc, char** argv)
{
	Rengine::Log::Init();

	auto app = Rengine::CreateApplication();
	app->Run();
	delete app;
}

#endif