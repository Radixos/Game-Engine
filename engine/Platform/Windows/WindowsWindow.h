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

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}