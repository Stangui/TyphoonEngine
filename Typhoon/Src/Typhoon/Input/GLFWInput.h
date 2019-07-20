#pragma once

#include "Typhoon/Input/Input.h"

namespace TyphoonEngine
{
	/// 
	///  Input Interface
	/// 
	class GLFWInput : public IInput
	{
	protected:

		/// 
		///  Keypress handler interface
		/// 
		virtual bool IsKeyPressedImpl( glm::int32 keyCode ) const override;

		/// 
		///  Mouse button handler interface
		/// 
		virtual bool IsMouseButtonPressedImpl( glm::int32 button ) const override;
		
		/// 
		///  Mouse position handler interface
		/// 
		virtual glm::vec2 GetMousePosImpl() const override;

	};

}

