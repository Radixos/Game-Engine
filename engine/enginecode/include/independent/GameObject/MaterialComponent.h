/**
\class MaterialComponent class
*/

#pragma once

#include <include\independent\Rendering\Material.h>

#include "GameObject.h"

namespace Engine {
	class MaterialComponent : public Component	//!<MaterialComponent class publicly inhariting from Component
	{
	private:
		std::shared_ptr<Material> m_material;
	public:
		MaterialComponent(const std::shared_ptr<Material>& material) : m_material(material) {}	//!<Constructor
		inline std::shared_ptr<Material> getMaterial() { return m_material; }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::UniformSet:
				std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
				m_material->setDataElement(data.first, data.second);
				return;
			}
		}
	};
}