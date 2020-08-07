#include "tuskpch.h"
#include "Window.h"

#include "GLFW/GLFWWindow.h"

namespace Tusk {

	Ref<Window> Window::create(const WindowCreateInfo& props)
	{
		return CreateRef<GLFWWindow>(props);
	}
}