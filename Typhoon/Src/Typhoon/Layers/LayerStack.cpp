#include "TyphoonPCH.h"
#include "LayerStack.h"
#include "Layer.h"

namespace TyphoonEngine
{

	//---------------------------------------------//
	LayerStack::LayerStack() : m_layerInsertIdx(0)
	{
	}

	//---------------------------------------------//
	LayerStack::~LayerStack()
	{
		for ( Layer* layer : m_layers )
		{
			TE_DELETE(layer);
		}
	}

	//---------------------------------------------//
	void LayerStack::PushLayer( Layer* layer )
	{
		m_layers.emplace( m_layers.begin() + m_layerInsertIdx, layer );
		++m_layerInsertIdx;
		layer->OnAttach();
	}

	//---------------------------------------------//
	void LayerStack::PushOverlay( Layer* layer )
	{
		m_layers.emplace_back( layer );
		layer->OnAttach();
	}

	//---------------------------------------------//
	void LayerStack::PopLayer( Layer* layer )
	{
		auto it = std::find( m_layers.begin(), m_layers.end(), layer );
		if ( it != m_layers.end() )
		{
			layer->OnDetach();
			m_layers.erase( it );
			--m_layerInsertIdx;
		}
	}

	//---------------------------------------------//
	void LayerStack::PopOverlay( Layer* layer )
	{
		auto it = std::find( m_layers.begin(), m_layers.end(), layer );
		if ( it != m_layers.end() )
		{
			layer->OnDetach();
			m_layers.erase( it );
		}
	}

}

