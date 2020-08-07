#pragma once

#include "../Utils/Defines.h"
#include "RendererAPI.h"
#include "Shader.h"

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
		/*
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			_rendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			_rendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			_rendererAPI->Clear();
		}
		*/
		/*static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}*/
	private:
		static Scope<RendererAPI> _rendererAPI;
	};
}