#include "EventTests.h"

TEST(Events, ResizeConstructor)
{
	int goWidth = re.getWidth();
	int goHeight = re.getHeight();
	Engine::EventType type = re.getEventType();

	EXPECT_EQ(goWidth, width);
	EXPECT_EQ(goHeight, height);
}

TEST(Event, DispatchTrue)
{
	Engine::EventDispatcher dispatcher(re);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Event, DispatchFalse)
{
	Engine::EventDispatcher dispatcher(ce);
	bool result = dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Event, DispatchHandledTrue)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeTrue, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_TRUE(result);
}

TEST(Event, DispatchHandledFalse)
{
	Engine::EventDispatcher dispatcher(re);
	dispatcher.dispatch<Engine::WindowResizeEvent>(std::bind(OnResizeFalse, std::placeholders::_1));
	bool result = re.handled();
	EXPECT_TRUE(result);
}