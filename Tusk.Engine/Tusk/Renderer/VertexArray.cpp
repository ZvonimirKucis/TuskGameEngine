#include "tuskpch.h"
#include "VertexArray.h"

#include "OpenGL/OpenGLVertexArray.h"

namespace Tusk {
	Ref<VertexArray> VertexArray::create() {
		 return CreateRef<OpenGLVertexArray>();
	}
}