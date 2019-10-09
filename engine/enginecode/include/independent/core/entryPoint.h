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

	auto application = Engine::startApplication();
	application->run();
	delete application;
	//return 0;
	system("pause");
}

