#pragma once

#include "glm/glm.hpp"
#include <string>

namespace TyphoonEngine
{
	namespace Renderers
	{

		///
		/// Texture loader
		///
		class Texture
		{
		
		public:
		
			///
			/// Constructor
			/// Parameters:
			///	 path - filepath to image
			///
			Texture(const std::string& path);

			///
			/// Destructor
			///
			~Texture();

			///
			/// Getters for texture properties
			///
			const glm::int32 GetWidth() const;
			const glm::int32 GetHeight() const;
			const glm::int32 GetBits() const;
			const glm::uint8* GetBuffer() const;

		private:

			/// filepath
			std::string m_filePath;
			
			/// Texture dims
			glm::int32 m_width, m_height, m_bpp;

			/// Pixel data 
			glm::uint8* m_buffer;

		};
		
	}
}

