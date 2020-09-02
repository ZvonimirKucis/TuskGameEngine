#include "tuskpch.h"

#include <GLFW/glfw3.h>

#include "GLFWWindow.h"

#include "Tusk/Events/ApplicationEvent.h"
#include "Tusk/Events/KeyEvent.h"
#include "Tusk/Events/MouseEvent.h"

namespace Tusk {
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		Logger::Error("GLFW Error (%d): %s", error, description);
	}

	GLFWWindow::GLFWWindow(const WindowCreateInfo& props) {
		init(props);
	}

	void GLFWWindow::init(const WindowCreateInfo& props) {
		_data.title = props.title;
		_data.width = props.width;
		_data.height = props.height;		

		glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);

#if _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		glfwWindowHint(GLFW_SAMPLES, 4);

		_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

		_context = GraphicsContext::create(_window);
		_context->init();

		glfwSetWindowUserPointer(_window, &_data);
		setVSync(true);

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

		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
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

	void GLFWWindow::setVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	bool GLFWWindow::isVSync() const {
		return _data.VSync;
	}

	void GLFWWindow::onUpdate() {
		glfwPollEvents();
		_context->swapBuffers();
	}

	GLFWWindow::~GLFWWindow() {
		if (_window) {
			glfwDestroyWindow(_window);
		}

		glfwTerminate();
	}

}