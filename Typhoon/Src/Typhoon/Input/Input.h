#pragma once

#include "Typhoon/Core.h"

namespace TyphoonEngine
{

	//
	// Platform-agnostic input interface
	//
	class IInput
	{
	public:

		//
		// Calls platform specific keypressed function
		// Parameters:
		//	keycode - unicode keycode
		//
		inline static bool IsKeyPressed( glm::int32 keyCode ) { return s_instance->IsKeyPressedImpl( keyCode ); }

		//
		// Calls platform specific mouse button pressed function
		// Parameters:
		//	button - button idx
		//
		inline static bool IsMouseButtonPressed( glm::int32 button ) { return s_instance->IsMouseButtonPressedImpl( button ); }

		//
		// Calls platform specific mouse position function
		//
		inline static glm::vec2 GetMousePos() { return s_instance->GetMousePosImpl(); }

	protected:

		//
		// Platform specific keypressed handler
		// Parameters:
		//	keycode - unicode keycode
		//
		virtual bool IsKeyPressedImpl( glm::int32 keyCode ) const = 0;

		//
		// Calls platform specific mouse button handler
		// Parameters:
		//	button - button Idx
		//
		virtual bool IsMouseButtonPressedImpl( glm::int32 button ) const = 0;

		//
		// Calls platform specific mouse position handler
		//
		virtual glm::vec2 GetMousePosImpl( ) const = 0;

	private:

		// Singleton
		static std::unique_ptr<IInput> s_instance;
	};

}