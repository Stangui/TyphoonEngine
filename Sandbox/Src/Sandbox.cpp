#include "TyphoonEngine.h"

//
// Sandbox client application
//
class SandboxApp : public TyphoonEngine::Application
{
public:

	SandboxApp() 
	{
	}
	
	virtual ~SandboxApp() override 
	{
	};

};

//
// Creates sandbox application
//
TyphoonEngine::Application* CreateApplication() 
{
	return new SandboxApp();
}