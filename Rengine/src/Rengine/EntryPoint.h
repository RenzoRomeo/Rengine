#pragma once

#include "Rengine/Application.h"
#include "Rengine/Log.h"

#ifdef RE_PLATFORM_WINDOWS

extern Rengine::Application* Rengine::CreateApplication();

int main(int argc, char** argv)
{
	Rengine::Log::Init();
	RE_CORE_WARN("Initialized Log!");
	int a = 2;
	RE_INFO("Hello! Var={0}", a);

	auto app = Rengine::CreateApplication();
	app->Run();
	delete app;
}

#endif