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

	m_resources.reset(new Engine::ResourceManager());
	m_resources->start(Engine::SystemSignal::None);

	m_OrthoCameraContr.reset(new Engine::FreeOrthoCameraController2D);
	m_OrthoCameraContr->init(0.0f, 0.0f, 800.f, 600.f);

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

	//m_FCVAO.reset(Engine::VertexArray::create());
	m_TPVAO.reset(Engine::VertexArray::create());

	m_resources->addVAO("FCVAO");
	//m_resources->addVAO("TPVAO");

	m_FCVertexBuffer.reset(Engine::VertexBuffer::create(FCvertices, sizeof(FCvertices), m_FClayout));
	m_resources->getVAO().get("FCVAO")->setVertexBuffer(m_FCVertexBuffer);

	m_FCindexBuffer.reset(Engine::IndexBuffer::create(indices, sizeof(indices)));
	m_resources->getVAO().get("FCVAO")->setindexBuffer(m_FCindexBuffer);

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

	m_FCcube.reset(Engine::Material::create(m_FCShader, m_resources->getVAO().get("FCVAO")));
	m_TPcube.reset(Engine::Material::create(m_TPShader, m_TPVAO));

	m_FCcube->setGeometry(m_FCVAO);
	m_TPcube->setGeometry(m_TPVAO);

	//////////////////////////////For text//////////////////////////////

	unsigned int textIndice[4] = { 0,1,2,3 };
	m_textRenderer.reset(Engine::Renderer::createBasicTextRenderer2D());

	m_textVAO.reset(Engine::VertexArray::create());

	textVBO.reset(Engine::VertexBuffer::create(textVerts, sizeof(textVerts), vbl));
	m_textVAO->setVertexBuffer(textVBO);

	textIBO.reset(Engine::IndexBuffer::create(textIndice, 4));
	m_textVAO->setindexBuffer(textIBO);

	m_textTexture.reset(Engine::Texture::createFromFile("assets/textures/DMU.png"));
	m_textShader.reset(Engine::Shader::create("assets/shaders/text.glsl"));

	m_textMaterial.reset(Engine::Material::create(m_textShader, m_textVAO));
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
	
	m_OrthoCameraContr->onUpdate(timestep);

	//m_OrthoCamera1->setPositionRotation(m_position, m_rotation);

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

	m_resources->getVAO().get("FCVAO")->bind();

	GLuint loc;

	m_FCShader->uploadData("u_MVP", &fcMVP[0][0]);

	m_renderer->submit(m_FCcube);

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
	glm::vec3 m_viewPosition(0.0f, 0.0f, -4.5f);

	m_TPShader->uploadData("u_MVP", &tpMVP[0][0]);
	m_TPShader->uploadData("u_model", &TPmodel[0][0]);
	//m_TPShader->uploadData("u_objectColour", &m_objectColour[0]);
	m_TPShader->uploadData("u_lightColour", &m_lightColour[0]);
	m_TPShader->uploadData("u_lightPos", &m_lightPosition[0]);
	m_TPShader->uploadData("u_viewPos", &m_viewPosition[0]);
	m_TPShader->uploadData("u_texData", (void*)m_texSlot);

	m_renderer->submit(m_TPcube);

	//////////////////////////////For text//////////////////////////////

	glm::mat4 textProjection = glm::ortho(0.f, 800.f, 600.f, 0.f);
	glm::mat4 textView = glm::mat4(1.0f);
	glm::mat4 textModel = glm::translate(glm::mat4(1.f), glm::vec3(100.f, 100.f, 0.f));

	m_texSlot = m_textTexture->getSlot();

	m_textMaterial->setDataElement("u_projection", (void*)&textProjection[0][0]);
	m_textMaterial->setDataElement("u_view", (void*)&textView[0][0]);
	m_textMaterial->setDataElement("u_model", (void*)&textModel[0][0]);
	m_textMaterial->setDataElement("u_texData", (void*)&m_texSlot);

	m_textRenderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(true));
	m_textRenderer->submit(m_textMaterial);
	m_textRenderer->actionCommand(Engine::RenderCommand::setOneMinusAlphaBlending(false));

	// End temporary code
#pragma endregion TempDrawCode
}

void GameLayer::onEvent(Engine::Event& event)
{

}