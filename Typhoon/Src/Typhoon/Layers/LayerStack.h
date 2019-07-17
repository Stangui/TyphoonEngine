#pragma once

#include <vector>

namespace TyphoonEngine
{

	class Layer;

	//
	// Layerstack manager
	// Handles application layering
	//
	class LayerStack
	{
	public:

		// Typedefs
		typedef std::vector<Layer*> LayerVec;
		typedef std::vector<Layer*>::iterator LayerVecIt;
		typedef unsigned int LayerIndex;

		//
		// Constructor/destructor
		//
		LayerStack();
		~LayerStack();

		// 
		// Pushes a layer into the stack on top of previous layers
		// Parameters:
		//	layer - pointer to layer to insert
		//
		void PushLayer( Layer* layer );

		// 
		// Pushes an overlay into the stack ALWAYS on top of layers
		// and above the previous overlay
		// Parameters:
		//	overlay - pointer to layer to insert
		//
		void PushOverlay( Layer* overlay );

		// 
		// Removes a layer from the stack
		// Parameters:
		//	layer - pointer to layer to remove
		//
		void PopLayer( Layer* layer );

		// 
		// Removes an overlay from the stack
		// Parameters:
		//	overlay - pointer to layer to remove
		//
		void PopOverlay( Layer* overlay );

		// Range-for support
		LayerVecIt begin() { return m_layers.begin(); }
		LayerVecIt end() { return m_layers.end(); }

	private:

		// Layers list
		LayerVec m_layers;

		// Index to insert next layer at
		LayerIndex m_layerInsertIdx;
	};

}
