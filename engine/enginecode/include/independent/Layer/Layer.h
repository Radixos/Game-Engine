/**
\class Layer class
*/

#pragma once

#include <memory>
#include <string>
#include <include\independent\Event\Event.h>

namespace Engine {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_debugName(name) {}	//!<Constructor
		virtual ~Layer() = default; /*{}*/	//!<Destructor

		virtual void onAttach() {}	//!<Virtual onAttach function
		virtual void onDetach() {}	//!<Virtual onDetach function
		virtual void onUpdate(float timestep) {}	//!<Virtual onUpdate function
		virtual void onImGuiRender() {}	//!<Virtual onImGuiRender function
		virtual void onEvent(Engine::Event& event) {}	//!<Virtual onEvent function

		inline const std::string& getName() const { return m_debugName; }	//!<Inline function returning name
	protected:
		std::string m_debugName;
	};
}