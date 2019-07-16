#pragma once

#include "Typhoon/Layers/Layer.h"

namespace TyphoonEngine
{

	class  ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void OnBegin();
		void OnEnd();

	private:

		float m_time;
	};

}

