#pragma once

#include "Typhoon/Events/Event.h"

namespace TyphoonEngine
{

	/// 
	///  Base application layer, receives engine events
	/// 
	class Layer
	{
	public:

		/// 
		///  Constructor
		///  Parameters:
		/// 	name - debug name
		///   bEnable - true/False 
		/// 
		Layer(const std::string& name = "Layer", bool bEnable = true);
		
		/// 
		///  Destructor
		/// 
		virtual ~Layer();

		/// 
		///  Called after layer is inserted into stack
		/// 
		virtual void OnAttach() {}

		/// 
		///  Called after layer is removed from stack
		/// 
		virtual void OnDetach() {}

		/// 
		///  Called during application update
		/// 
		virtual void OnUpdate(float deltaTime) {}

		/// 
		///  Called after layer is inserted into stack
		/// 
		virtual void OnEvent(Event& Evt) {}

		/// 
		///  Called during GUI rendering
		/// 
		virtual void OnImGuiRender() {}
		
		/// 
		///  Sets whether this layer is active
		///  Parameters:
		/// 	bEnabled - True/False
		/// 
		inline void SetEnabled( bool bEnable ) { m_bEnabled = bEnable; }
		
		/// 
		///  Returns whether this layer is active
		/// 
		inline bool IsEnabled() const { return m_bEnabled; }

		/// 
		///  Returns the debug name
		/// 
		const std::string& GetName() const { return m_name; }

	private:

		///  Debug name
		std::string m_name;

		///  Active flag
		bool m_bEnabled = false;
	};

}
