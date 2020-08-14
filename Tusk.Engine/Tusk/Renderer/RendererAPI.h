#pragma once

#include <glm/glm.hpp>
#include "../Platform/Window.h"
#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

namespace Tusk {

	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;

		virtual void init(const Ref<Window> window) = 0;
		virtual void clearScreen() = 0;
		virtual void drawFrame() = 0;
		
		virtual void bindVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void bindIndexBuffer(IndexBuffer* indexBuffer) = 0;
		virtual void bindTexture(const Ref<Texture>& texture) = 0;
		virtual void bindShader(const Ref<Shader> shader) = 0;

		virtual void beginDrawing() = 0;
		virtual void submitToDraw(const Ref<Shader>& shader) = 0;
		virtual void endDrawing() = 0;

		virtual void handleResize() = 0;

		static Scope<RendererAPI> create();
	};

}