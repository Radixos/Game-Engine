#pragma once

#include "include/independent/Layer/Layer.h"
#include "include/independent/Rendering/Material.h"
#include "include/independent/Rendering/Texture.h"
#include <include\independent\Rendering\UniformBuffer.h>
#include <include\independent\Rendering\Renderer.h>
#include "include/independent/systems/Log.h"
#include <include\independent\core\Timer.h>
#include <include\independent\windows\window.h>
#include <include\platform\GLFW\GLFWWindowsSystem.h>

	class GameLayer : public Engine::Layer
	{
	private:
		std::shared_ptr<Engine::Material> m_FCcube;	//Flat colour cube material
		std::shared_ptr<Engine::Material> m_TPcube;	//Textured Phone cube material
		std::shared_ptr<Engine::UniformBuffer> m_UBOMatrices;	//Uniform buffer object for view
		std::shared_ptr<Engine::UniformBuffer> m_UBOLights;	//Uniform buffer object for light
		//std::shared_ptr<Engine::Texture> m_numberTex;	//Number texture
		//std::shared_ptr<Engine::Texture> m_letterTex;	//Letter texture
		std::shared_ptr<Engine::Log> m_logger;
		std::shared_ptr<Engine::Timer> m_timer;
		std::shared_ptr<Engine::Window> m_windows;
		std::shared_ptr<Engine::GLFWWindowsSystem> m_system;
		std::shared_ptr<Engine::VertexArray> m_FCVAO;
		std::shared_ptr<Engine::VertexArray> m_TPVAO;
		std::shared_ptr<Engine::VertexBuffer> m_FCVertexBuffer;
		std::shared_ptr<Engine::VertexBuffer> m_TPVertexBuffer;
		std::shared_ptr<Engine::IndexBuffer> m_FCindexBuffer;
		std::shared_ptr<Engine::IndexBuffer> m_TPindexBuffer;
		std::shared_ptr<Engine::Texture> m_TPNumberTex;
		std::shared_ptr<Engine::Texture> m_TPLetterTex;
		std::shared_ptr<Engine::Renderer> m_renderer;
		std::shared_ptr<Engine::Shader> m_FCShader;
		std::shared_ptr<Engine::Shader> m_TPShader;

		glm::mat4 FCmodel, TPmodel;

		Engine::BufferLayout m_TPlayout =
		{
			{Engine::ShaderDataType::Float3},
			{Engine::ShaderDataType::Float3},
			{Engine::ShaderDataType::Float2},
		};
		Engine::BufferLayout m_FClayout =
		{
			{Engine::ShaderDataType::Float3},
			{Engine::ShaderDataType::Float3},
		};

		glm::mat4 m_FCmodel;
		glm::mat4 m_TPmodel; 
		unsigned int m_texSlot;
		glm::vec3 m_lightColour;
		glm::vec3 m_lightPosition;
		glm::vec3 m_viewPosition;
		Engine::SceneData sceneData;
		bool m_goingUp = false;	//Is the cube going up?
		float m_timeSummed = 10.f;	//How much time has elapsed?
	public:
		GameLayer(const std::string& name = "Layer");
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Engine::Event& event) override;
	};