#include "TyphoonEngine.h"

class ExampleLayer : public TyphoonEngine::Layer
{
public:

	ExampleLayer()
	{
	}

	virtual ~ExampleLayer() override
	{
	}

	void OnUpdate() override
	{

	}

	void OnEvent( TyphoonEngine::Event& Evt ) override
	{
	}

	bool OnKeyPressed( TyphoonEngine::KeyPressedEvent& Evt )
	{
		return false;
	}

};

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