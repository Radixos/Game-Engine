/**
\class GLFWWindowImpl.h class
*/

#pragma once

#include "windows/window.h"
#include <GLFW\glfw3.h>

namespace Engine {

	class GLFWWindowImpl : public Window
	{
	private:
		GLFWwindow* m_nativeWindow;

		void init(const WindowProperties& properties) override;
		void close();
		WindowProperties m_properties;
		std::function<void(Event&)> m_callback; // General OnEvent call back - bound to Application::OnEvent(e)
		float m_aspectRatio; //!<Aspect ratio on creation, ussed to correct viewport
	public:
		GLFWWindowImpl(const WindowProperties& properties);
		~GLFWWindowImpl();
		void onUpdate(float timestep) override;
		void onResize(unsigned int width, unsigned int height) override;
		void setVSync(bool VSync) override;
		void setEventCallback(const std::function<void(Event&)>& callback) override;
		inline unsigned int getWidth() const override { return m_properties.m_width; }
		inline unsigned int getHeight() const override { return m_properties.m_height; }
		inline void* getNativeWindow() const override { return m_nativeWindow; }
		inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }
		inline bool isVSync() const override { return m_properties.m_isVSync; }
	};

}