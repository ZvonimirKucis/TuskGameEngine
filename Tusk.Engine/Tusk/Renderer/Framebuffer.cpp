#include "tuskpch.h"
#include "Framebuffer.h"

#include "Renderer.h"

#include "OpenGL/OpenGLFramebuffer.h"

namespace Tusk {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		return CreateRef<OpenGLFramebuffer>(spec);
	}
}

