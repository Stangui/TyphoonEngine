#pragma once

namespace TyphoonEngine
{
	class Timestep
	{

	public:

		virtual ~Timestep() {}

		virtual float GetSeconds() const = 0;
		virtual int32_t GetMilliseconds() const = 0;

		static Timestep* Create();

	};

}