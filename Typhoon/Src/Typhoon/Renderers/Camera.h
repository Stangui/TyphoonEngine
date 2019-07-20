#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//
		// Scene camera implementation
		//
		class Camera
		{
		public:

			//
			// Projection type for this camera
			//
			enum class PROJECTION_TYPE : glm::uint8
			{
				Orthographic, 
				Persepctive,
				Fisheye
			};

			//
			// Constructor
			// Parameters:
			//	left - frustum near-plane left position
			//	right - frustum near-plane right position
			//	top - frustum near-plane top position
			//	bottom - frustum near-plane bottom position
			//
			Camera();
			virtual ~Camera();

			//
			// Initialise camera
			//
			virtual void Init();

			//
			// Sets the projection type for this camera
			//
			void SetProjectionType(PROJECTION_TYPE type);
			
			//
			// Sets the projection type for this camera
			//
			const PROJECTION_TYPE GetProjectionType( ) const;

			//
			// Gets/Sets the position
			//
			void SetPosition(const glm::vec3& pos);
			const glm::vec3& GetPosition() const;

			//
			// Gets/Sets the rotation
			//
			void SetRotation(float rotation);
			const float GetRotation() const;

			//
			// Gets/Sets clip planes
			//
			void SetClipPlanes( float nearClip, float farClipB );
			const float GetNearClip() const;
			const float GetFarClip() const;

			//
			// Gets/Sets fov
			//
			void SetFovY( float fov );
			const float GetFovY() const;

			//
			// Gets/Sets clip planes
			//
			void SetAspectRatio( float aspect );
			const float GetAspectRatio() const;

			//
			// Gets matrices
			//
			const glm::mat4& GetViewMatrix() const;
			const glm::mat4& GetProjectionMatrix() const;
			const glm::mat4& GetViewProjectionMatrix() const;

		private:

			void _recalculateViewMatrix();

			glm::mat4 m_projMat;
			glm::mat4 m_viewMat;
			glm::mat4 m_viewProjMat;

			glm::vec3 m_position;
			float m_rotation;

			float m_fov;
			float m_aspectRatio;
			float m_nearClip;
			float m_farClip;

			PROJECTION_TYPE m_type;
		};

	}
}

