/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENG_CORE_WARN("Initialized Log!");
	ENG_CORE_INFO("Hello!");

	auto application = Engine::startApplication();
	application->run();
	delete application;

	//return 0;
	system("pause");
}

