#include "tuskpch.h"
#include "GraphicsContext.h"

#include "OpenGL/OpenGLContext.h"

namespace Tusk {
	Scope<GraphicsContext> GraphicsContext::create(void* window) {
		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}
}