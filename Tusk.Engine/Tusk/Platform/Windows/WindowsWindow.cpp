#include "tuskpch.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "WindowsWindow.h"

#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

#include "../../Renderer/Vulkan/VulkanContext.h"

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

		_context = new VulkanContext(_window);
		_context->init();

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

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();
		_context->swapBuffers();
	}

	WindowsWindow::~WindowsWindow() {
		if (_window) {
			glfwDestroyWindow(_window);
		}

		glfwTerminate();
	}

}