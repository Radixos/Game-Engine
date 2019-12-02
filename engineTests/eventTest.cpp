#include "eventTest.h"
//#include "EventTests.h"	!!!!!!!!!!!!!!!!!!!!!!!!!!

TEST(Events, ResizeConstructor)
{
	int gotWidth = re.getWidth();
	int gotHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(gotWidth, width);
	EXPECT_EQ(gotHeight, height);
}

TEST(Events, DispatchTrue)
{
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchFalse)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));	//Not false?
	EXPECT_FALSE(result);
}

TEST(Events, DispatchTrue)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchTrue)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeFalse, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_FALSE(result);
}