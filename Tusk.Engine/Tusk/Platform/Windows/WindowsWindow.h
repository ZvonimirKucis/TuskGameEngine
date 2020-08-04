#pragma once

#include "../Window.h"

#include <GLFW/glfw3.h>

namespace Tusk {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowCreateInfo& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		unsigned int getWidth() const override { return _data.width; }
		unsigned int getHeight() const override { return _data.height; }

		void setEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }

		inline virtual void* getNativeWindow() const { return _window;  }
	private:
		virtual void init(const WindowCreateInfo& props);

	private:
		GLFWwindow* _window;

		struct WindowData
		{
			std::string title;
			I32 width, height;

			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};
}