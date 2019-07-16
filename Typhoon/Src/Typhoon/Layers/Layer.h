#pragma once

#include "Typhoon/Events/Event.h"

namespace TyphoonEngine
{

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer", bool bEnable = true);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& Evt) {}
		virtual void OnImGuiRender() {}

		inline void SetEnabled( bool bEnable ) { m_bEnabled = bEnable; }
		inline bool IsEnabled() const { return m_bEnabled; }

		const std::string& GetName() const { return m_name; }

	private:

		std::string m_name;
		bool m_bEnabled = false;
	};

}
