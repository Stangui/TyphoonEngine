#pragma once

#include "Typhoon/Timestep.h"

namespace TyphoonEngine
{

	class WindowsTimestep : public Timestep
	{
	public:

		WindowsTimestep();
		virtual ~WindowsTimestep() override;

		virtual float GetSeconds() const override;
		virtual int32_t GetMilliseconds() const override;

	};

}