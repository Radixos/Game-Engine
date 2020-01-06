#include "engine_pch.h"
#include "Layer/LayerStack.h"
#include "Layer/Layer.h"

/*TO DO:
fix commented lines*/

namespace Engine {
	LayerStack::LayerStack()
	{
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (std::shared_ptr<Layer> layer : m_layers)
		{
			layer->onDetach();
			layer.reset();
		}
	}

	void LayerStack::pushLayer(std::shared_ptr<Layer> layer)
	{
		//m_layers.emplace(m_layers.begin() + m_layerInsert, layer);	//m_layerInsertIndex
		//m_layerInsert++;	//m_layerInsertIndex
		//m_layerInsert = m_layers.emplace(m_layerInsert, layer);

		m_layers.push_back(layer);
		layer->onAttach();
	}

	void LayerStack::pushOverlay(std::shared_ptr<Layer> overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(std::shared_ptr<Layer> layer)
	{
		/*auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsert, layer);
		if (it != m_layers.begin() + m_layerInsert)
		{
			layer->onDetach();
			m_layers->erase(it);
			m_layerInsert--;
		}*/
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerInsert--;
		}
	}

	void LayerStack::popOverlay(std::shared_ptr<Layer> overlay)
	{
		//auto it = std::find(m_layers.begin() + m_layerInsert, m_layers.end(), overlay);
		//if (it != m_layers.end())
		//{
		//	overlay->onDetach();
		//	//???
		//	m_layerInsert--;
		//}
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}
}