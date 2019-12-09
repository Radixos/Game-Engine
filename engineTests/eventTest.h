#pragma once

#include <gtest/gtest.h>

#include "Event/Event.h"
#include<Event/EventDispatcher.h>
#include "Event/EventSubclass.h"

const int width = 1024;
const int height = 720;
Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}

bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}

bool OnCloseTrue(Engine::WindowCloseEvent& e)
{
	return true;
}

bool OnCloseFalse(Engine::WindowCloseEvent& e)
{
	return false;
}