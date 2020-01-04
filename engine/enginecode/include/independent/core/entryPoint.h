/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
//#include "engine.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	
	auto application = Engine::startApplication();
	application->run();
	delete application;
}