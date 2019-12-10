#pragma once

#include "engine_pch.h"
#include <include\independent\Event\Event.h>
#include <any>

namespace Engine {
	class GameObject;

	class Component
	{
	protected:
		GameObject* m_owner = nullptr;	//Owner of the component, using a raw pointer as there is no ownership yet
		virtual void sendMessage(const ComponentMessage& msg);
	public:
		virtual void onAttach(GameObject* owner) { m_owner = owner; };
		virtual void onDetach() { m_owner = nullptr; };
		virtual void onUpdate(float timestep) {};
		virtual void onEvent(Event& e) {};
		virtual void receiveMessage(const ComponentMessage& msg) = 0;
	};

	enum class ComponentMessageType {
		None = 0,
		PositionIntegrate, PositionSet, RelativePositionSet,
		VelocityIntegrate, VelocitySetLinear, VelocitySetAngular,
		AccelerationSet,
		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved,
		UniformSet, TextureSet
	};

	class ComponentMessage
	{
	public:
		//ComponentMessage(ComponentMessage type, std::any data) : m_msgType(type), m_msgData(data) {};
		ComponentMessageType m_msgType;	//!<Message type
		std::any m_msgData;	//!<Data associated with the message (could use a void *)
	};

	class GameObject
	{
	protected:
		std::vector<std::shared_ptr<Component>> m_components;
	public:
		void onUpdate(float timestep);
		void onEvent(Event& e);
		void addComponent(const std::shared_ptr<Component>& comp);
		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter);
		template<typename G>
		std::vector<std::shared_ptr<Component>>::iterator getComponent()
		{
			auto result = m_components.end();
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (typeid(decltype(*(it - get()))).hash_code() == typeid(G).hash_code()) return it;
			}
			return result;
		}
		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
	};
}