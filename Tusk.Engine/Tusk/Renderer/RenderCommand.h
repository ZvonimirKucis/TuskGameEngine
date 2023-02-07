#pragma once

#include "RendererAPI.h"

namespace Tusk {

	class RenderCommand
	{
	public:
		static void init() {
			_rendererAPI->init();
		}

		static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			_rendererAPI->setViewport(x, y, width, height);
		}

		static void setClearColor(const glm::vec4& color) {
			_rendererAPI->setClearColor(color);
		}

		static void setDepthFunction(DepthFunc func) {
			_rendererAPI->setDepthFunc(func);
		}

		static void clear() {
			_rendererAPI->clear();
		}

		static void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
			_rendererAPI->drawIndexed(vertexArray, count);
		}

	private:
		static Scope<RendererAPI> _rendererAPI;
	};

}
