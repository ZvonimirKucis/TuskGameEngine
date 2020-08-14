#include "tuskpch.h"

#include "VulkanRendererAPI.h"

namespace Tusk {

	void VulkanRendererAPI::init(const Ref<Window> window) {
		_instance = CreateScope<VulkanInstance>(window);
	}

	void VulkanRendererAPI::clearScreen() {
		_instance->clearScreen();
	}

	void VulkanRendererAPI::handleResize() {
		_instance->setFramebufferResized();
	}

	void VulkanRendererAPI::drawFrame() {
		_instance->drawFrame();
	}

	void VulkanRendererAPI::bindIndexBuffer(IndexBuffer* indexBuffer) {
		_instance->bindIndexBuffer(indexBuffer);
	}

	void VulkanRendererAPI::bindVertexBuffer(VertexBuffer* vertexBuffer) {
		_instance->bindVertexBuffer(vertexBuffer);
	}

	void VulkanRendererAPI::bindTexture(const Ref<Texture>& texture) {
		_instance->bindTexture(texture);
	}

	void VulkanRendererAPI::bindShader(const Ref<Shader> shader) {
		_instance->bindShader(shader);
	}

	void VulkanRendererAPI::beginDrawing() {
		_instance->beginDrawing();
	}

	void VulkanRendererAPI::submitToDraw(const Ref<Shader>& shader) {
		_instance->submitToDraw(shader);
	}

	void VulkanRendererAPI::endDrawing() {
		_instance->endDrawing();
	}

	VulkanRendererAPI::~VulkanRendererAPI() {
	}
}