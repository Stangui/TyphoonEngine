#pragma once

#include "Typhoon/Layers/Layer.h"

namespace TyphoonEngine
{

	//
	// Adds ImGui UI rendering
	//
	class  ImGuiLayer : public Layer
	{

	public:

		//
		// Constructor/Destructor
		//
		ImGuiLayer();
		~ImGuiLayer();

		//
		// Initialises ImGui on layer attach
		//
		void OnAttach() override;

		//
		// Destroys ImGui on layer detach
		//
		void OnDetach() override;

		//
		// Used to draw ImGui UI geometry 
		//
		void OnImGuiRender() override;

		//
		// Initialises ImGui for a frame render
		//
		void OnBegin();
		//
		// Ends an ImGui frame render
		//
		void OnEnd();

	private:

		// frametime
		float m_time;
	};

}

