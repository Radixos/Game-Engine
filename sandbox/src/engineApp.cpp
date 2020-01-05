/** \file engineApp.cpp
*/
#include "engineApp.h"
#include <GameLayer.h>
#include <UILayer.h>

engineApp::engineApp()
{
	m_layerStack->pushLayer(std::make_shared<GameLayer>(GameLayer("Game Layer")));
	m_layerStack->pushLayer(std::make_shared<UILayer>(UILayer("UI Layer")));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}