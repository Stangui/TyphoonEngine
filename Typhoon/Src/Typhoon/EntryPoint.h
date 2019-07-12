#pragma once

extern TyphoonEngine::Application* CreateApplication();

#if TYPHOON_PLATFORM_WINDOWS

int main( int argc, char** argv )
{
	TyphoonEngine::Log::Init();

	auto App = CreateApplication();
	App->Run();
	delete App;

	return 0;
}

#elif TYPHOON_PLATFORM_LINUX

int main( int argc, char** argv )
{
	auto App = CreateApplication();
	App->Run();
	delete App;

	return 0;
}

#else
	
	#error platform not supported!

#endif

