#pragma once

#include "Typhoon/Layers/Layer.h"

namespace TyphoonEngine
{

	class  ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent( Event& Evt );

	private:

		float m_time;
	};

}

