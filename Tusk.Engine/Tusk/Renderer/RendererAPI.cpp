#include "tuskpch.h"
#include "RendererAPI.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace Tusk {
	Scope<RendererAPI> RendererAPI::Create() {
		return CreateScope<OpenGLRendererAPI>();
	}
}