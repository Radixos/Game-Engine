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
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void onUpdate(float timestep) override;

		inline unsigned int getWidth() const override { return m_Data.Width; }
		inline unsigned int getHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void setEventCallback(const eventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			eventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}