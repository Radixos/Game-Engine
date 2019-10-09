/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENG_CORE_WARN("Initialized Log!");
	int a = 5;
	ENG_CLIENT_INFO("Hello! Var = {0}", a);	// WHY DOES Var HAVE TO BE 0 OR IT WON'T WORK?
	
	Engine::Timestep ts;
	ENG_CORE_TRACE("Delta Time: = {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds()); // TO MAKE TIME AND FRAMES UPDATE FOLLOW LAYERS TUTORIAL

	auto application = Engine::startApplication();
	application->run();
	delete application;
	//return 0;
	system("pause");
}

