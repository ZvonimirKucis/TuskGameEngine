#include "tuskpch.h"
#include "Renderer.h"
#include "RendererCommand.h"

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

	void Renderer::submit(const Ref<Shader>& shader, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const Ref<Texture>& texture) {
		RenderCommand::bindIndexBuffer(indexBuffer);
		RenderCommand::bindVertexBuffer(vertexBuffer);
		RenderCommand::bindTexture(texture);
		RenderCommand::bindShader(shader);
		RenderCommand::submitToDraw(shader);
	}

	void Renderer::endScene() {
		RenderCommand::endDrawing();
	}
}