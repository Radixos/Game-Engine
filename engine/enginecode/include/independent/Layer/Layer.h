#pragma once

#include <memory>
#include <string>
#include <engine.h>

namespace Engine {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_debugName(name) {}	//???
		virtual ~Layer() = default; /*{}*/

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(float timestep) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Engine::Event& event) {}

		inline const std::string& getName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}