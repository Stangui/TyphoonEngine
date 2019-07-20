#include "TyphoonPCH.h"

#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"
#include "Typhoon/Core.h"

#if TE_PLATFORM_WINDOWS
#	include "DirectX/DirectXBuffer.h"
#endif	//TE_PLATFORM_WINDOWS

#if TE_PLATFORM_VULKAN
#	include "Vulkan/VulkanBuffer.h"
#endif	//TE_PLATFORM_WINDOWS

#if TE_PLATFORM_MACOS
#	include "MACOS/MetalBuffer.h"
#endif	//TE_PLATFORM_WINDOWS

namespace TyphoonEngine
{
	namespace Renderers
	{

		IVertexBuffer* IVertexBuffer::Create( const float* vertices, glm::uint32 size )
		{
			switch ( IRenderer::GetRenderAPI() )
			{
			case RendererAPI::API::None:
			{
				TE_ASSERT( false, "RenderingAPI::None is not supported!" );
				break;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexBuffer( vertices, size );
			}
#if TE_PLATFORM_WINDOWS
			case RenderAPI::DirectX:
			{
				TE_ASSERT( false, "RenderingAPI::DirectX is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_WINDOWS
#if TE_PLATFORM_VULKAN
			case RendererAPI::API::Vulkan:
			{
				TE_ASSERT( false, "RenderingAPI::Vulkan is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_VULKAN
#if TE_PLATFORM_MACOS
			case RendererAPI::API::Metal:
			{
				TE_ASSERT( false, "RenderingAPI::Metal is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_MACOS
			}
			return nullptr;
		}

		IIndexBuffer* IIndexBuffer::Create( const glm::uint32* indices, glm::uint32 count )
		{
			switch ( IRenderer::GetRenderAPI() )
			{
			case RendererAPI::API::None:
			{
				TE_ASSERT( false, "RenderingAPI::None is not supported!" );
				break;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLIndexBuffer( indices, count );
			}
#if TE_PLATFORM_WINDOWS
			case RendererAPI::API::DirectX:
			{
				TE_ASSERT( false, "RenderingAPI::DirectX is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_WINDOWS
#if TE_PLATFORM_WINDOWS
			case RendererAPI::API::Vulkan:
			{
				TE_ASSERT( false, "RenderingAPI::Vulkan is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_VULKAN
#if TE_PLATFORM_WINDOWS
			case RendererAPI::API::Metal:
			{
				TE_ASSERT( false, "RenderingAPI::Metal is not supported!" );
				break;
			}
#endif	//TE_PLATFORM_MACOS
			}
			return nullptr;
		}

	}
}