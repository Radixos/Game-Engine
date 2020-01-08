#include "eventTest.h"

/////////////////////////////////////////RESIZE/////////////////////////////////////////

TEST(Events, ResizeConstructor)
{
	int gotWidth = re.getWidth();
	int gotHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(gotWidth, width);
	EXPECT_EQ(gotHeight, height);
}

TEST(Events, DispatchResizeTrue)
{
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchResizeFalse)
{
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleForResizeTrue)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	bool result = re.isHandled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleForResizeFalse)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeFalse, std::placeholders::_1));
	bool result = re.isHandled();
	EXPECT_FALSE(result);
}

/////////////////////////////////////////CLOSE/////////////////////////////////////////

TEST(Events, CloseConstructor)
{
	//Engine::EventType type = ce.getEventType();
}

TEST(Events, DispatchCloseTrue)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchCloseFalse)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

//TEST(Events, DispatchHandleForCloseTrue)
//{
//	Engine::EventDispatcher dispatcher(ce);
//	dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseTrue, std::placeholders::_1));
//	bool result = ce.isHandled();
//	EXPECT_TRUE(result);
//}

TEST(Events, DispatchHandleForCloseFalse)
{
	Engine::EventDispatcher dispatcher(ce);
	dispatcher.dispatch<Engine::WindowCloseEvent>(std::bind(OnCloseFalse, std::placeholders::_1));
	bool result = ce.isHandled();
	EXPECT_FALSE(result);
}

/////////////////////////////////////////LOST FOCUS/////////////////////////////////////////

TEST(Events, LostFocusConstructor)
{
	int gotPosX = le.getposX();
	int gotPosY = le.getposY();
	Engine::EventType type = le.getEventType();

	EXPECT_EQ(gotPosX, posX);
	EXPECT_EQ(gotPosY, posY);
}

TEST(Events, DispatchLostFocusTrue)
{
	Engine::EventDispatcher dispatcher(le);
	bool result = dispatcher.dispatch<Engine::WindowLostFocus>(std::bind(OnLostFocusTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchLostFocusFalse)
{
	Engine::EventDispatcher dispatcher(le);
	bool result = dispatcher.dispatch<Engine::WindowLostFocus>(std::bind(OnLostFocusFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleForLostFocusTrue)
{
	Engine::EventDispatcher dispatcher(le);
	dispatcher.dispatch<Engine::WindowLostFocus>(std::bind(OnLostFocusTrue, std::placeholders::_1));
	bool result = le.isHandled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleForLostFocusFalse)
{
	Engine::EventDispatcher dispatcher(le);
	dispatcher.dispatch<Engine::WindowLostFocus>(std::bind(OnLostFocusFalse, std::placeholders::_1));
	bool result = le.handled(false);
	EXPECT_FALSE(result);
}

/////////////////////////////////////////MOUSE MOVED/////////////////////////////////////////

TEST(Events, MouseMovedConstructor)
{
	int gotOffsetX = mme.getoffsetX();
	int gotOffsetY = mme.getoffsetY();
	Engine::EventType type = le.getEventType();

	EXPECT_EQ(gotOffsetX, offsetX);
	EXPECT_EQ(gotOffsetY, offsetY);
}

TEST(Events, DispatchMouseMovedTrue)
{
	Engine::EventDispatcher dispatcher(mme);
	bool result = dispatcher.dispatch<Engine::MouseMoved>(std::bind(OnMouseMovedTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchMouseMovedFalse)
{
	Engine::EventDispatcher dispatcher(mme);
	bool result = dispatcher.dispatch<Engine::MouseMoved>(std::bind(OnMouseMovedFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleForMouseMovedTrue)
{
	Engine::EventDispatcher dispatcher(mme);
	dispatcher.dispatch<Engine::MouseMoved>(std::bind(OnMouseMovedTrue, std::placeholders::_1));
	bool result = mme.isHandled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleForMouseMovedFalse)
{
	Engine::EventDispatcher dispatcher(mme);
	dispatcher.dispatch<Engine::MouseMoved>(std::bind(OnMouseMovedFalse, std::placeholders::_1));
	bool result = mme.handled(false);
	EXPECT_FALSE(result);
}

/////////////////////////////////////////MOUSE BUTTON PRESSED/////////////////////////////////////////

TEST(Events, MouseButtonPressedConstructor)
{
	int gotButton = mpe.getButton();
	Engine::EventType type = mpe.getEventType();

	EXPECT_EQ(gotButton, button);
}

TEST(Events, DispatchMouseButtonPressedTrue)
{
	Engine::EventDispatcher dispatcher(mpe);
	bool result = dispatcher.dispatch<Engine::MouseButtonPressed>(std::bind(OnMouseButtonPressedTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchMouseButtonPressedFalse)
{
	Engine::EventDispatcher dispatcher(mpe);
	bool result = dispatcher.dispatch<Engine::MouseButtonPressed>(std::bind(OnMouseButtonPressedFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleForMouseButtonPressedTrue)
{
	Engine::EventDispatcher dispatcher(mpe);
	dispatcher.dispatch<Engine::MouseButtonPressed>(std::bind(OnMouseButtonPressedTrue, std::placeholders::_1));
	bool result = mpe.isHandled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleForMouseButtonPressedFalse)
{
	Engine::EventDispatcher dispatcher(mpe);
	dispatcher.dispatch<Engine::MouseButtonPressed>(std::bind(OnMouseButtonPressedFalse, std::placeholders::_1));
	bool result = mpe.handled(false);
	EXPECT_FALSE(result);
}

/////////////////////////////////////////MOUSE BUTTON RELEASED/////////////////////////////////////////

TEST(Events, MouseButtonReleasedConstructor)
{
	int gotButton = mre.getButton();
	Engine::EventType type = mre.getEventType();

	EXPECT_EQ(gotButton, button);
}

TEST(Events, DispatchMouseButtonReleasedTrue)
{
	Engine::EventDispatcher dispatcher(mre);
	bool result = dispatcher.dispatch<Engine::MouseButtonReleased>(std::bind(OnMouseButtonReleasedTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchMouseButtonReleasedFalse)
{
	Engine::EventDispatcher dispatcher(mre);
	bool result = dispatcher.dispatch<Engine::MouseButtonReleased>(std::bind(OnMouseButtonReleasedFalse, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleForMouseButtonReleasedTrue)
{
	Engine::EventDispatcher dispatcher(mre);
	dispatcher.dispatch<Engine::MouseButtonReleased>(std::bind(OnMouseButtonReleasedTrue, std::placeholders::_1));
	bool result = mre.isHandled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleForMouseButtonReleasedFalse)
{
	Engine::EventDispatcher dispatcher(mre);
	dispatcher.dispatch<Engine::MouseButtonReleased>(std::bind(OnMouseButtonReleasedFalse, std::placeholders::_1));
	bool result = mre.handled(false);
	EXPECT_FALSE(result);
}