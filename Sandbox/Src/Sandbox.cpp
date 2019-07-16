#include "TyphoonEngine.h"

//--------------------------------------------------//
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

//--------------------------------------------------//
TyphoonEngine::Application* CreateApplication() 
{
	return new SandboxApp();
}