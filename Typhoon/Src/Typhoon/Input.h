#pragma once

#include "Core.h"

namespace TyphoonEngine
{

	// Input Interface
	class IInput
	{
	public:

		inline static bool IsKeyPressed( int32 keyCode ) { return s_instance->IsKeyPressedImpl( keyCode ); }
		inline static bool IsMouseButtonPressed( int32 button ) { return s_instance->IsMouseButtonPressedImpl( button ); }
		inline static Vec2f GetMousePos() { return s_instance->GetMousePosImpl(); }

	protected:

		virtual bool IsKeyPressedImpl( int32 keyCode ) const = 0;
		virtual bool IsMouseButtonPressedImpl( int32 button ) const = 0;
		virtual Vec2f GetMousePosImpl( ) const = 0;

	private:

		static std::unique_ptr<IInput> s_instance;
	};

}