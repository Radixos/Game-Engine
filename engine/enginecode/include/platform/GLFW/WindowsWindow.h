/**
\class WindowsWindow class
*/
#pragma once

#include "windows/window.h"
//#include "Engine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

#ifdef ENG_ENABLE_ASSERTS
	#define ENG_ASSERT(x, ...) { if(!(x)) {ENG_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENG_CORE_ASSERT(x, ...) { if(!(x)) { ENG_CORE_ERROR("Assertion Failed {0}", __VA_ARGS); __debugbreak(); } }
#else
	#define ENG_ASSERT(x, ...)
	#define ENG_CORE_ASSERT(x, ...)
#endif

namespace Engine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);	//!<Window constructor
		virtual ~WindowsWindow();	//!<Window destructor

		void onUpdate(float timestep) override;	//!<onUpdate function for window

		inline unsigned int getWidth() const override { return m_data.m_width; }	//!<Inline funtion for getting the width
		inline unsigned int getHeight() const override { return m_data.m_height; }	//!<Inline funtion for getting the height

		// Window attributes
		inline void setEventCallback(const std::function<void(Event&)>& callback) override	//!<Inline function for setting event callback
		{ 
			m_callback = callback;
			glfwSetWindowUserPointer(m_Window, &m_callback);
		}
		void setVSync(bool enabled) override;	//!<Overrided function for setting the VSync
		bool isVSync() const override;	//!<Overrided boolean function for setting the VSync
		void onResize(unsigned int width, unsigned int height) override;	//!<Overrided function for resizing
		inline bool isFullScreenMode() const override { return m_data.m_isFullScreen; }	//!<Inline overrided function for setting full screen mode
		inline void* getNativeWindow() const override { return m_Window; }	//!<Inline overrided function for returning the window

	private:
		void init(const WindowProperties& props) override;	//!<Overrided initialize function
		void close() override;	//!<Function for closing the window

		GLFWwindow* m_Window;
		//scope<GraphicsContext> m_Context;

		/*struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;


			EventCallbackFn EventCallback;
		};*/
		WindowProperties m_data;
		std::function<void(Event&)> m_callback;
	};

}