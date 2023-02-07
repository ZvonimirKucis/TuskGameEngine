#pragma once

#include "Tusk/Platform/Window.h"
#include "Tusk/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Tusk {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(const WindowCreateInfo& props);
		virtual ~GLFWWindow() override;

		void onUpdate() override;

		unsigned int getWidth() const override { return _data.width; }
		unsigned int getHeight() const override { return _data.height; }

		void setEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* getNativeWindow() const override { return _window; };
	private:
		virtual void init(const WindowCreateInfo& props);

	private:
		GLFWwindow* _window;
		Scope<GraphicsContext> _context;

		struct WindowData
		{
			std::string title;
			uint32_t width = 0, height = 0;
			bool VSync = true;

			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};
}