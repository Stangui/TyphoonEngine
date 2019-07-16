#pragma once

#include "Core.h"

namespace TyphoonEngine
{

	// Input Interface
	class IInput
	{
	public:

		inline static bool IsKeyPressed( glm::int32 keyCode ) { return s_instance->IsKeyPressedImpl( keyCode ); }
		inline static bool IsMouseButtonPressed( glm::int32 button ) { return s_instance->IsMouseButtonPressedImpl( button ); }
		inline static glm::vec2 GetMousePos() { return s_instance->GetMousePosImpl(); }

	protected:

		virtual bool IsKeyPressedImpl( glm::int32 keyCode ) const = 0;
		virtual bool IsMouseButtonPressedImpl( glm::int32 button ) const = 0;
		virtual glm::vec2 GetMousePosImpl( ) const = 0;

	private:

		static std::unique_ptr<IInput> s_instance;
	};

}