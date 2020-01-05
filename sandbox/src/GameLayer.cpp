#include "GameLayer.h"
#include <glm\ext\matrix_transform.hpp>

GameLayer::GameLayer(const std::string& name) : Layer(name)
{
	// Create a basic 3D
	m_renderer.reset(Engine::Renderer::createBasic3D());
	// Enable standard depth detest (Z-buffer)
	m_renderer->actionCommand(Engine::RenderCommand::setDepthTestLessCommand(true));
	// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
	m_renderer->actionCommand(Engine::RenderCommand::setBackfaceCullingCommand(true));

	//Vertices and indices
	float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
	};

	float TPvertices[8 * 24] = {
		-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
		 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
		 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
		-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
		-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
		 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
		 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
		-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
		-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
		 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
		 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
		-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
		-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
		 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
		 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
		-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
		-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
		-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
		-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
		-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
		0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
		0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
	};

	unsigned int indices[3 * 12] = {
		2, 1, 0,
		0, 3, 2,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		14, 13, 12,
		12, 15, 14,
		18, 17, 16,
		16, 19, 18,
		20, 21, 22,
		22, 23, 20
	};

	m_FCVertexBuffer.reset(Engine::VertexBuffer::create(FCvertices, sizeof(FCvertices), m_FClayout));
	m_FCVAO->setVertexBuffer(m_FCVertexBuffer);

	m_FCindexBuffer.reset(Engine::IndexBuffer::create(indices, sizeof(indices)));
	m_FCVAO->setindexBuffer(m_FCindexBuffer);

	m_TPVertexBuffer.reset(Engine::VertexBuffer::create(TPvertices, sizeof(TPvertices), m_TPlayout));
	m_TPVAO->setVertexBuffer(m_TPVertexBuffer);

	m_TPindexBuffer.reset(Engine::IndexBuffer::create(indices, sizeof(indices)));
	m_TPVAO->setindexBuffer(m_TPindexBuffer);

	m_FCShader.reset(Engine::Shader::create("assets/shaders/flatColour.glsl"));
	m_TPShader.reset(Engine::Shader::create("assets/shaders/texturedPhong.glsl"));

	m_TPNumberTex.reset(Engine::Texture::createFromFile("assets/textures/letterCube.png"));
	m_TPLetterTex.reset(Engine::Texture::createFromFile("assets/textures/numberCube.png"));

	FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
	TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));
}

void GameLayer::onAttach()
{

}

void GameLayer::onDetach()
{

}

void GameLayer::onUpdate(float timestep)
{

}

void GameLayer::onEvent(Engine::Event& event)
{

}