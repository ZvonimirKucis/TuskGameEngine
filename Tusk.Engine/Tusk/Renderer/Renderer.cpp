#include "tuskpch.h"
#include "Renderer.h"
#include "RendererCommand.h"

#include "../Utils/Logger.h"

namespace Tusk {

	//RendererAPI Renderer::_rendererAPI = RendererAPI::Vulkan;
	void Renderer::init(const Ref<Window> window) {
		RenderCommand::init(window);
	}

	void Renderer::clear() {
		RenderCommand::clear();
	}

	void Renderer::update() {
		RenderCommand::drawFrame();
	}

	/*void Renderer::Shutdown()
	{
		//Renderer2D::Shutdown();
	}*/

	/*void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		//RenderCommand::SetViewport(0, 0, width, height);
	}*/

	void Renderer::beginScene() {
		RenderCommand::beginDrawing();
		//s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::submit(const Ref<Shader>& shader) {
		RenderCommand::bindShader(shader);
		RenderCommand::submitToDraw(shader);
	}

	void Renderer::endScene() {
		RenderCommand::endDrawing();
	}
}