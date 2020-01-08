#pragma once

#include <gtest/gtest.h>

#include "Event/Event.h"
#include <Event/EventDispatcher.h>
#include "Event/EventSubclass.h"

/////////////////////////////////////////RESIZE/////////////////////////////////////////

const int width = 1024;
const int height = 720;
Engine::WindowResizeEvent re(width, height);

bool OnResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}

bool OnResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}

/////////////////////////////////////////CLOSE/////////////////////////////////////////

Engine::WindowCloseEvent ce;

bool OnCloseTrue(Engine::WindowCloseEvent& e)
{
	return true;
}

bool OnCloseFalse(Engine::WindowCloseEvent& e)
{
	return false;
}

/////////////////////////////////////////LOST FOCUS/////////////////////////////////////////

int posX;
int posY;
Engine::WindowLostFocus le(posX, posY);

bool OnLostFocusTrue(Engine::WindowLostFocus& e)
{
	return true;
}

bool OnLostFocusFalse(Engine::WindowLostFocus& e)
{
	return false;
}

/////////////////////////////////////////MOUSE MOVED/////////////////////////////////////////

int offsetX;
int offsetY;
Engine::MouseMoved mme(offsetX, offsetY);

bool OnMouseMovedTrue(Engine::MouseMoved& e)
{
	return true;
}

bool OnMouseMovedFalse(Engine::MouseMoved& e)
{
	return false;
}

/////////////////////////////////////////MOUSE BUTTON PRESSED/////////////////////////////////////////

int button;
Engine::MouseButtonPressed mpe(button);

bool OnMouseButtonPressedTrue(Engine::MouseButtonPressed& e)
{
	return true;
}

bool OnMouseButtonPressedFalse(Engine::MouseButtonPressed& e)
{
	return false;
}