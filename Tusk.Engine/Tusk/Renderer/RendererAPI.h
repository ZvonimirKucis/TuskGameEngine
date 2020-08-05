#pragma once

#include <glm/glm.hpp>
#include "../Platform/Window.h"

namespace Tusk {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, Vulkan = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void init(const Ref<Window> window) = 0;
		/*virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;*/

		//virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API getAPI() { return _API; }
		static Scope<RendererAPI> Create();
	private:
		static API _API;
	};

}