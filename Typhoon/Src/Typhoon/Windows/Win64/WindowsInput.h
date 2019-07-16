#pragma once

#include "Typhoon/Input.h"

namespace TyphoonEngine
{
	// Input Interface
	class WindowsInput : public IInput
	{
	protected:

		virtual bool IsKeyPressedImpl( glm::int32 keyCode ) const override;
		virtual bool IsMouseButtonPressedImpl( glm::int32 button ) const override;
		virtual glm::vec2 GetMousePosImpl() const override;

	};

}

