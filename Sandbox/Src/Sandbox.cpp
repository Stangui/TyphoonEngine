#include "TyphoonEngine.h"

//--------------------------------------------------//
class SandboxApp : public TyphooEngine::Application
{
public:

	SandboxApp() {}
	virtual ~SandboxApp() override {};

};

//--------------------------------------------------//
TyphooEngine::Application* CreateApplication() 
{
	return new SandboxApp();
}