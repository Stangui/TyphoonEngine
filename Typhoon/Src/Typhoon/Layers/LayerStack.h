#pragma once

#include <vector>

namespace TyphoonEngine
{

	class Layer;

	class LayerStack
	{
	public:

		typedef std::vector<Layer*> LayerVec;
		typedef std::vector<Layer*>::iterator LayerVecIt;

		LayerStack();
		~LayerStack();

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );
		void PopLayer( Layer* layer );
		void PopOverlay( Layer* layer );

		// Range-for 
		LayerVecIt begin() { return m_layers.begin(); }
		LayerVecIt end() { return m_layers.end(); }

	private:

		LayerVec m_layers;
		LayerVecIt m_layerInsert;
	};

}
