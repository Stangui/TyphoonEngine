#pragma once

#include "Typhoon/Input.h"

namespace TyphoonEngine
{
	// Input Interface
	class WindowsInput : public IInput
	{
	protected:

		virtual bool isKeyPressedImpl( int32 keyCode ) const override;
		virtual bool isMouseButtonPressedImpl( int32 button ) const override;
		virtual Vec2f getMousePosImpl() const override;

	};

}

