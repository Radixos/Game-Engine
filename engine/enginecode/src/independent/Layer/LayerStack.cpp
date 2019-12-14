#include "engine_pch.h"
#include "Layer/LayerStack.h"

/*TO DO:
fix commented lines*/

namespace Engine {
	LayerStack::LayerStack()
	{
		//m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (std::shared_ptr<Layer> layer : m_layers)
		{
			layer->onDetach();
			layer.reset();
		}
		//m_Layers->onDetach();
		//m_Layer.reset();
	}

	void LayerStack::pushLayer(std::shared_ptr<Layer> layer)
	{
		//m_layers.emplace(m_layers.begin() + m_layerInsert, layer);	//m_layerInsertIndex
		//m_layerInsert++;	//m_layerInsertIndex
		////m_layerInsert = m_layers.emplace(m_layerInsert, layer);
	}

	void LayerStack::pushOverlay(std::shared_ptr<Layer> overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(std::shared_ptr<Layer> layer)
	{
		/*auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
		if (it != m_layers.begin() + m_layerInsertIndex)
		{
			layer->onDetach();
			m_layers->erase(it);
			m_layerInsertIndex--;
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
		//auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
		//if (it != m_layers.end())
		//{
		//	overlay->onDetach();
		//	//???
		//	m_layerInsertIndex--;
		//}
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}
}