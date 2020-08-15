#include "tuskpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "OpenGL/OpenGLTexture.h"

namespace Tusk {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		return CreateRef<OpenGLTexture2D>(width, height);
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		return CreateRef<OpenGLTexture2D>(path);
	}

}