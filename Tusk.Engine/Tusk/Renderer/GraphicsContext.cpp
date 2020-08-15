#include "tuskpch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "OpenGL/OpenGLContext.h"

namespace Tusk {
	Scope<GraphicsContext> GraphicsContext::Create(void* window) {
		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}
}