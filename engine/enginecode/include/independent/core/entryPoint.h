/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
//#include "engine.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENG_CORE_WARN("Initialized Log!");
	int a = 5;
	ENG_CLIENT_INFO("Hello! Var = {0}", a);
	
	//Engine::Timer ts;
	//ENG_CORE_TRACE("Delta Time: = {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds()); // TO MAKE TIME AND FRAMES UPDATE NEED TO FOLLOW LAYERS TUTORIAL

	auto application = Engine::startApplication();
	application->run();
	delete application;
	//return 0;
	//system("pause");
}