#define GLFW_INCLUDE_VULKAN

#include "tuskpch.h"
#include "WindowsWindow.h"

#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

namespace Tusk {
	
	Window* Window::create(const WindowCreateInfo& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowCreateInfo& props) {
		init(props);
	}

	void WindowsWindow::init(const WindowCreateInfo& props) {
		_data.title = props.title;
		_data.width = props.width;
		_data.height = props.height;

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(_window, &_data);

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();
	}

	WindowsWindow::~WindowsWindow() {
		if (_window) {
			glfwDestroyWindow(_window);
		}

		glfwTerminate();
	}

}