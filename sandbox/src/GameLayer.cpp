#include "GameLayer.h"
#include <glm\ext\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>

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

	m_FCVAO.reset(Engine::VertexArray::create());
	m_TPVAO.reset(Engine::VertexArray::create());

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

	m_FCcube.reset(Engine::Material::create(m_FCShader, m_FCVAO));
	m_TPcube.reset(Engine::Material::create(m_TPShader, m_TPVAO));
}

void GameLayer::onAttach()
{

}

void GameLayer::onDetach()
{

}

void GameLayer::onUpdate(float timestep)
{
	m_renderer->actionCommand(Engine::RenderCommand::setClearColourCommand(0.0f, 0.0f, 1.0f, 1.0f));
	m_renderer->actionCommand(Engine::RenderCommand::ClearDepthColourBufferCommand(0.0f, 0.0f, 1.0f, 1.0f));
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
		glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
		glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
	);

	// Code to make the cube move.
	glm::mat4 FCtranslation, TPtranslation;

	if (m_goingUp)
	{
		FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f));
		TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f));
	}
	else
	{
		FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * timestep, 0.0f));
		TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * timestep, 0.0f));
	}

	/*if (m_timer->getTimeSinceMarkerStart() > 4.0f)
	{
		m_timer->setMarkerStart();
		m_goingUp = !m_goingUp;
	}*/

	m_timeSummed += timestep;
	if (m_timeSummed > 4.f)
	{
		m_goingUp = !m_goingUp;
		m_timeSummed = 0.0f;
		//reset m_timeSummed
	}

	FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
	TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

	// End of code to make the cube move.

	glm::mat4 fcMVP = projection * view * FCmodel;

	m_FCShader->bind();

	m_FCVAO->bind();

	GLuint loc;

	m_FCShader->uploadData("u_MVP", &fcMVP[0][0]);

	m_renderer->submit(m_FCcube);
	//glDrawElements(GL_TRIANGLES, m_FCVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

	glm::mat4 tpMVP = projection * view * TPmodel;
	m_TPShader->bind();
	m_TPVAO->bind();

	unsigned int m_texSlot;

	if (m_goingUp) m_texSlot = m_TPLetterTex->getSlot();
	else m_texSlot = m_TPNumberTex->getSlot();

	m_TPShader->bind();
	m_TPVAO->bind();

	//glm::vec3 m_objectColour(0.2f, 0.8f, 0.5f);
	glm::vec3 m_lightColour(1.0f, 1.0f, 1.0f);
	glm::vec3 m_lightPosition(0.0f, 3.0f, -6.0f);
	glm::vec3 m_viewPosition(0.0f, 0.0f, -4.5f);	//m_viewPosition = glm::vec3(0.0f, 0.0f, -4.5f);

	m_TPShader->uploadData("u_MVP", &tpMVP[0][0]);
	m_TPShader->uploadData("u_model", &TPmodel[0][0]);
	//m_TPShader->uploadData("u_objectColour", &m_objectColour[0]);
	m_TPShader->uploadData("u_lightColour", &m_lightColour[0]);
	m_TPShader->uploadData("u_lightPos", &m_lightPosition[0]);
	m_TPShader->uploadData("u_viewPos", &m_viewPosition[0]);
	m_TPShader->uploadData("u_texData", (void*)m_texSlot);

	m_renderer->submit(m_TPcube);
	//glDrawElements(GL_TRIANGLES, m_TPVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

	// End temporary code
#pragma endregion TempDrawCode

	m_windows->onUpdate(timestep);

	//if (time > 3.0f)
	//{
	//	WindowResizeEvent e(1024, 720);
	//	onEvent(e);
	//	m_running = false;
	//	//ENG_CORE_INFO("Time elapsed: {0}. Shutting down.", time);
	//}
	//end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<float> diff = end - start;
	//s_timestep = diff.count();
}

void GameLayer::onEvent(Engine::Event& event)
{

}