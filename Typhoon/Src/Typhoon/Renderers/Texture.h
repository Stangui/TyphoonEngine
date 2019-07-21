#pragma once

#include "glm/glm.hpp"
#include <string>

namespace TyphoonEngine
{
	namespace Renderers
	{

		class ITexture
		{
		
		public:
		
			ITexture(const std::string& path);
			virtual ~ITexture();

			void Load( const std::string& path ) = 0;
			const glm::int32 GetWidth() const = 0;
			const glm::int32 GetHeight() const = 0;
			const glm::int32 GetBits() const = 0;
			const glm::uint8* GetBuffer() const = 0;

		};
		
	}
}

