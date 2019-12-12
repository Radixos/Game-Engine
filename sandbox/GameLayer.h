//#pragma once
//
//#include "include/independent/Layer/Layer.h"
//#include "include/independent/Rendering/Material.h"
//#include "include/independent/Rendering/Texture.h"
//#include <include\independent\Rendering\UniformBuffer.h>
//
////namespace Engine {
//	class GameLayer : public Engine::Layer	//Why not just "Layer"
//	{
//	private:
//		std::shared_ptr<Engine::Material> m_FCcube;	//Flat colour cube material
//		std::shared_ptr<Engine::Material> m_TPcube;	//Textured Phone cube material
//		std::shared_ptr<Engine::UniformBuffer> m_UBOMatrices;	//Uniform buffer object for view
//		std::shared_ptr<Engine::UniformBuffer> m_UBOLights;	//Uniform buffer object for light
//		std::shared_ptr<Engine::Texture> m_numberTex;	//Number texture
//		std::shared_ptr<Engine::Texture> m_letterTex;	//Letter texture
//		glm::mat4 m_FCmodel;
//		glm::mat4 m_TPmodel;
//		unsigned int m_texSlot;
//		glm::vec3 m_lightColour;
//		glm::vec3 m_lightPosition;
//		glm::vec3 m_viewPosition;
//		Engine::SceneData sceneData;
//		bool m_goingUp = false;	//Is the cube going up?
//		float m_timeSummed = 10.f;	//How much time has elapsed?
//	public:
//		GameLayer(const std::string& name = "Layer") : Layer(name) {};
//		void onAttach() override;
//		void onDetach() override;
//		void onUpdate(float timestep) override;
//		void onEvent(Engine::Event& event) override;
//	};
////}