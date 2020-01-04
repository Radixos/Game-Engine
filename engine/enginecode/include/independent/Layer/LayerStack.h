/**
\class LayerStack class
*/

#pragma once

#include "Layer.h"

namespace Engine {
	class LayerStack	//!<LayerStack class
	{
	public:
		LayerStack();	//!<Constructor
		~LayerStack();	//!<Destructor

		void pushLayer(std::shared_ptr<Layer> layer);	//!<pushLayer function
		void pushOverlay(std::shared_ptr<Layer> overlay);	//!<pushOverlay function
		void popLayer(std::shared_ptr<Layer> layer);	//!<popLayer function
		void popOverlay(std::shared_ptr<Layer> overlay);	//!<popOverlay function

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_layers.begin(); }	//!<Vector begin
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_layers.end(); }	//!<Vector end
		//std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		//std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return m_layers.begin(); }	//!<Vector begin
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return m_layers.end(); }	//!<Vector end
		//std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		//std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_layers;
		std::vector<Layer*>::iterator m_layerInsert;
	};
}