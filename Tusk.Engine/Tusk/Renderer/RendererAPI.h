#pragma once

#include <glm/glm.hpp>
#include "../Platform/Window.h"
#include "Shader.h"

namespace Tusk {

	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;

		virtual void init(const Ref<Window> window) = 0;
		virtual void clearScreen() = 0;
		virtual void drawFrame() = 0;

		virtual void bindShader(const Ref<Shader> shader) = 0;

		virtual void beginDrawing() = 0;
		virtual void submitToDraw(const Ref<Shader>& shader) = 0;
		virtual void endDrawing() = 0;
		/*virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;*/

		//virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		static Scope<RendererAPI> create();
	};

}