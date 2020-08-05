#include "tuskpch.h"
#include "Window.h"

#include "Windows/WindowsWindow.h"

namespace Tusk {

	Ref<Window> Window::create(const WindowCreateInfo& props)
	{
		return CreateRef<WindowsWindow>(props);
	}
}