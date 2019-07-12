#pragma once

#include "Core.h"

namespace TyphoonEngine
{

	// Input Interface
	class IInput
	{
	public:

		inline static bool isKeyPressed( int32 keyCode ) { return s_instance->isKeyPressedImpl( keyCode ); }
		inline static bool isMouseButtonPressed( int32 button ) { return s_instance->isMouseButtonPressedImpl( button ); }
		inline static Vec2f getMousePos() { return s_instance->getMousePosImpl(); }

	protected:

		virtual bool isKeyPressedImpl( int32 keyCode ) const = 0;
		virtual bool isMouseButtonPressedImpl( int32 button ) const = 0;
		virtual Vec2f getMousePosImpl( ) const = 0;

	private:

		static std::unique_ptr<IInput> s_instance;
	};

}