#pragma once

#include "../Utils/Defines.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "Buffer.h"

namespace Tusk {

	class RenderCommand{
	public:
		static void init(const Ref<Window> window)
		{
			_rendererAPI->init(window);
		}

		static void clear()
		{
			_rendererAPI->clearScreen();
		}

		static void drawFrame() {
			_rendererAPI->drawFrame();
		}

		static void bindIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
			_rendererAPI->bindIndexBuffer(indexBuffer);
		}

		static void bindVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
			_rendererAPI->bindVertexBuffer(vertexBuffer);
		}

		static void bindShader(const Ref<Shader>& shader) {
			_rendererAPI->bindShader(shader);
		}

		static void beginDrawing() {
			_rendererAPI->beginDrawing();
		}

		static void submitToDraw(const Ref<Shader>& shader) {
			_rendererAPI->submitToDraw(shader);
		}

		static void endDrawing() {
			_rendererAPI->endDrawing();
		}

		static void handleResize() {
			_rendererAPI->handleResize();
		}

	private:
		static Scope<RendererAPI> _rendererAPI;
	};
}