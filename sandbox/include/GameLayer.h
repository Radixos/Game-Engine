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
#include "include/independent/Camera/FreeOrthoCameraController2D.h"
#include "include/independent/Camera/PerspectiveCamera3D.h"
#include "include/independent/systems/ResourceManager.h"

	class GameLayer : public Engine::Layer
	{
	private:
		std::shared_ptr<Engine::Material> m_FCcube;	//!<Flat colour cube material
		std::shared_ptr<Engine::Material> m_TPcube;	//!<Textured Phone cube material
		std::shared_ptr<Engine::Material> m_textMaterial;	//!<Material for text
		std::shared_ptr<Engine::UniformBuffer> m_UBOMatrices;	//!<Uniform buffer object for view
		std::shared_ptr<Engine::UniformBuffer> m_UBOLights;	//!<Uniform buffer object for light
		std::shared_ptr<Engine::Texture> m_numberTex;	//!<Number texture
		std::shared_ptr<Engine::Texture> m_letterTex;	//!<Letter texture
		std::shared_ptr<Engine::Log> m_logger;	//!<Logger
		std::shared_ptr<Engine::Timer> m_timer;	//!<Timer for measuring time and actions
		std::shared_ptr<Engine::Window> m_windows;	//!<Window
		std::shared_ptr<Engine::GLFWWindowsSystem> m_windowsSystem;	//!<WindowsSystem
		std::shared_ptr<Engine::VertexArray> m_FCVAO;	//!<Vertex Array for flat colour cube
		std::shared_ptr<Engine::VertexArray> m_TPVAO;	//!<Vertex Array for textured cube
		std::shared_ptr<Engine::VertexArray> m_textVAO;	//!<Vertex Array for text
		std::shared_ptr<Engine::VertexBuffer> m_FCVertexBuffer;	//!<Vertex Buffer for flat colour cube
		std::shared_ptr<Engine::VertexBuffer> m_TPVertexBuffer;	//!<Vertex Buffer for textured cube
		std::shared_ptr<Engine::VertexBuffer> m_textVBO;	//!<VertexBuffer for text
		std::shared_ptr<Engine::IndexBuffer> m_FCindexBuffer;	//!<Index Buffer for flat colour cube
		std::shared_ptr<Engine::IndexBuffer> m_TPindexBuffer;	//!<Index Buffer for textured cube
		std::shared_ptr<Engine::IndexBuffer> m_textIBO;	//!<IndexBuffer for text
		std::shared_ptr<Engine::Texture> m_TPNumberTex;	//!<Number texture for textured cube
		std::shared_ptr<Engine::Texture> m_TPLetterTex;	//!<Letter texture for textured cube
		std::shared_ptr<Engine::Texture> m_textTexture;	//!<Texture for text
		std::shared_ptr<Engine::Renderer> m_renderer;	//!<Renderer
		std::shared_ptr<Engine::Renderer> m_textRenderer;	//!<Renderer for text
		std::shared_ptr<Engine::Shader> m_FCShader;	//!<Shader for flat colour cube
		std::shared_ptr<Engine::Shader> m_TPShader;	//!<Shader for textured cube
		std::shared_ptr<Engine::Shader> m_textShader;	//!<Shader for text
		std::shared_ptr<Engine::ResourceManager> m_resources;	//!<Resource manager

		//Camera2DController
		std::shared_ptr<Engine::FreeOrthoCameraController2D> m_OrthoCameraContr;

		//std::shared_ptr<Engine::PerspectiveCamera3D> m_PerspCamera;

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

		float textVerts[4 * 4] =
		{
			0.f, 0.f, 0.f, 0.f,
			0.f, 100.f, 0.f, 1.f,
			250.f, 100.f, 1.f, 1.f,
			250.f, 0.f, 1.f, 0.f
		};	//!<Text Vertex for text

		Engine::BufferLayout vbl = { {Engine::ShaderDataType::Float2}, {Engine::ShaderDataType::Float2} };


		//glm::mat4 m_FCmodel;
		//glm::mat4 m_TPmodel; 
		unsigned int m_texSlot;
		glm::vec3 m_lightColour;
		glm::vec3 m_lightPosition;
		glm::vec3 m_viewPosition;
		Engine::SceneData sceneData;
		bool m_goingUp = false;	//!<Is the cube going up?
		float m_timeSummed = 2.0f;	//!<Time elapsed
	public:
		GameLayer(const std::string& name = "Layer");
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Engine::Event& event) override;
	};