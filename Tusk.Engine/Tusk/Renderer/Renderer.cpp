#include "tuskpch.h"
#include "Renderer.h"
#include "RendererCommand.h"

#include "../Utils/Logger.h"

namespace Tusk {

	void Renderer::init(const Ref<Window> window) {
		RenderCommand::init(window);
	}

	void Renderer::clear() {
		RenderCommand::clear();
	}

	void Renderer::update() {
		RenderCommand::drawFrame();
	}

	void Renderer::onWindowResize()
	{
		RenderCommand::handleResize();
	}

	void Renderer::beginScene() {
		RenderCommand::beginDrawing();
	}

	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexBuffer>& vertexBuffer) {
		RenderCommand::bindVertexBuffer(vertexBuffer);
		RenderCommand::bindShader(shader);
		RenderCommand::submitToDraw(shader);
	}

	void Renderer::endScene() {
		RenderCommand::endDrawing();
	}
}