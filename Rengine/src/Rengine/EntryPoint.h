#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern Rengine::Application* Rengine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Rengine::CreateApplication();
	app->Run();
	delete app;
}

#endif