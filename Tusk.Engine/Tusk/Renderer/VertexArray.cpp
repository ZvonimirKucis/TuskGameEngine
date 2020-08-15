#include "tuskpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Tusk {
	Ref<VertexArray> VertexArray::Create() {
		 return CreateRef<OpenGLVertexArray>();
	}
}