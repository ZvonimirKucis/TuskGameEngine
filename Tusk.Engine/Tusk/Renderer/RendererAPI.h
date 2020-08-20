#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Tusk {
	enum class DepthFunc {
		LEQUAL, LESS
	};

	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;

		virtual void init() = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void setDepthFunc(DepthFunc func) = 0;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		static Scope<RendererAPI> create();
	};

}
