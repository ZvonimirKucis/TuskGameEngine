#pragma once

#include "../Platform/Window.h"
#include "RendererCommand.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

namespace Tusk {

	class Renderer {
	public:
		static void init(const Ref<Window> window);
		static void clear();
		static void update();

		static void onWindowResize();

		static void beginScene();
		static void endScene();

		static void submit(const Ref<Shader>& shader, const Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const Ref<Texture>& texture);
	private:
	};
}