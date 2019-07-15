#include "TyphoonEngine.h"

//--------------------------------------------------//
class SandboxApp : public TyphoonEngine::Application
{
public:

	SandboxApp() 
	{
		PushLayer( new TyphoonEngine::ImGuiLayer() );
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