#include "TyphoonPCH.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hPP"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//------------------------------------------------------------//
		Camera::Camera() :
			m_type( PROJECTION_TYPE::Orthographic )
			, m_position( glm::vec3( 0.f ) )
			, m_rotation( 0.f )
			, m_viewMat( glm::mat4( 1.f ) )
			, m_projMat( glm::ortho( -1.6f, 1.6f, -0.9f, 0.9f, -1.f, 1.f ) )
			, m_viewProjMat( glm::mat4( 1.f ) )
			, m_fov( 45.f )
			, m_aspectRatio( 16.f / 9.f )
			, m_nearClip( 1.f )
			, m_farClip( 100.f )
		{
			m_viewProjMat = m_projMat * m_viewMat;
		}

		void Camera::Init()
		{
			switch ( m_type )
			{
			case PROJECTION_TYPE::Persepctive:
			{
				m_projMat = glm::perspective( m_fov, m_aspectRatio, m_nearClip, m_farClip );
				break;
			}
			case PROJECTION_TYPE::Fisheye:
			{
				m_fov = 180.f;
				m_projMat = glm::perspective( m_fov, m_aspectRatio, m_nearClip, m_farClip );
				break;
			}
			}
		}

		//------------------------------------------------------------//
		Camera::~Camera()
		{
		}

		//------------------------------------------------------------//
		void Camera::_recalculateViewMatrix()
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.f), m_position) *
				glm::rotate( glm::mat4( 1.f ), glm::radians(m_rotation), glm::vec3( 0.f, 0.f, 1.f ) );

			m_viewMat = glm::inverse(transform);
			m_viewProjMat = m_projMat * m_viewMat;
		}

		//------------------------------------------------------------//
		void Camera::SetProjectionType(PROJECTION_TYPE type)
		{
			m_type = type;
		}

		//------------------------------------------------------------//
		const Camera::PROJECTION_TYPE Camera::GetProjectionType() const
		{
			return m_type;
		}

		//------------------------------------------------------------//
		void Camera::SetPosition(const glm::vec3& position)
		{
			m_position = position;
			_recalculateViewMatrix();
		}

		//------------------------------------------------------------//
		const glm::vec3& Camera::GetPosition() const
		{
			return m_position;
		}

		//------------------------------------------------------------//
		void Camera::SetRotation(float rotation)
		{
			m_rotation = rotation;
			_recalculateViewMatrix();
		}

		//------------------------------------------------------------//
		const float Camera::GetRotation() const
		{
			return m_rotation;
		}

		//------------------------------------------------------------//
		void Camera::SetFovY( float fov )
		{
			m_fov = fov;
		}

		//------------------------------------------------------------//
		const float Camera::GetFovY() const
		{
			return m_fov;
		}

		//------------------------------------------------------------//
		void Camera::SetAspectRatio( float aspect )
		{
			m_aspectRatio = aspect;
		}

		//------------------------------------------------------------//
		const float Camera::GetAspectRatio() const
		{
			return m_aspectRatio;
		}

		//------------------------------------------------------------//
		void Camera::SetClipPlanes(float nearClip, float farClip)
		{
			m_nearClip = nearClip;
			m_farClip = farClip;
		}

		//------------------------------------------------------------//
		const float Camera::GetNearClip() const
		{
			return m_nearClip;
		}

		//------------------------------------------------------------//
		const float Camera::GetFarClip() const
		{
			return m_farClip;
		}

		//------------------------------------------------------------//
		const glm::mat4& Camera::GetViewMatrix() const
		{
			return m_viewMat;
		}

		//------------------------------------------------------------//
		const glm::mat4& Camera::GetProjectionMatrix() const
		{
			return m_viewMat;
		}

		//------------------------------------------------------------//
		const glm::mat4& Camera::GetViewProjectionMatrix() const
		{
			return m_viewProjMat;
		}

	}
}
