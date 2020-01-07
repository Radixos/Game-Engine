/**
/class window class
*/
#pragma once

#include "graphicsContext.h"
#include <string>
#include <functional>

namespace Engine {

	class Event; // Be replaced

	struct WindowProperties
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isFullScreen;
		bool m_isVSync;

		WindowProperties(const std::string& title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {}	//!<WindowProperties constructor
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual void init(const WindowProperties& properties) = 0;	//Virtual function for initialising the window
		virtual void close() = 0;	//Virtual function for closing
		virtual ~Window() {};	//Virtual destructor
		virtual void onUpdate(float timestep) = 0;	//!<Virtual on update function
		virtual void onResize(unsigned int width, unsigned int height) = 0;	//!<Virtual on resize function
		virtual void setVSync(bool VSync) = 0;	//!<Virtual function for setting the VSync
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;	//Virtual function for setting the event callback
		virtual unsigned int getWidth() const = 0;	//!<Virtual function for getting the width
		virtual unsigned int getHeight() const = 0;	//!<Virtual function for getting the height
		virtual void* getNativeWindow() const = 0;	//!<Virtual function for getting the native window
		virtual bool isFullScreenMode() const = 0;	//!<Virtual function for setting the full screen mode
		virtual bool isVSync() const = 0;	//!<Virtual boolean function for setting the VSync	

		static Window* create(const WindowProperties& properties = WindowProperties());	//!<Static function to create a window
	protected:
		std::shared_ptr<GraphicsContext> m_context;
	};
}

