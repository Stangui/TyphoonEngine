#pragma once

///  Client defined application
extern TyphoonEngine::Application* CreateApplication();

#if defined( TYPHOON_PLATFORM_WINDOWS ) || defined( TYPHOON_PLATFORM_LINUX )

/// 
///  Creates, runs and destroys application
/// 
int main( int argc, char** argv )
{
	TyphoonEngine::Log::Init();

	auto App = CreateApplication();
	App->Run();
	delete App;

	return 0;
}

#else
	
	#error platform not supported!

#endif

