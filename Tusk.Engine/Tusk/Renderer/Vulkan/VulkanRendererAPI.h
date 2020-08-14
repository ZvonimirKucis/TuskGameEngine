#pragma once
#include "../RendererAPI.h"
#include "VulkanInstance.h"
#include "../Buffer.h"
#include "../Texture.h"

namespace Tusk {

	class VulkanRendererAPI : public RendererAPI {
	public:
		virtual ~VulkanRendererAPI() override;

		virtual void init(const Ref<Window> window) override;
		virtual void clearScreen() override;
		virtual void drawFrame() override;

		virtual void bindIndexBuffer(IndexBuffer* indexBuffer) override;
		virtual void bindVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void bindTexture(const Ref<Texture>& texture) override;
		virtual void bindShader(const Ref<Shader> shader) override;

		virtual void beginDrawing() override;
		virtual void submitToDraw(const Ref<Shader>& shader) override;
		virtual void endDrawing() override;

		virtual void handleResize() override;

	private:
		Scope<VulkanInstance> _instance;
	};
}