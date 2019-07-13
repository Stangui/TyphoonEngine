#pragma once

#include "Typhoon/Input.h"

namespace TyphoonEngine
{
	// Input Interface
	class WindowsInput : public IInput
	{
	protected:

		virtual bool IsKeyPressedImpl( int32 keyCode ) const override;
		virtual bool IsMouseButtonPressedImpl( int32 button ) const override;
		virtual Vec2f GetMousePosImpl() const override;

	};

}

