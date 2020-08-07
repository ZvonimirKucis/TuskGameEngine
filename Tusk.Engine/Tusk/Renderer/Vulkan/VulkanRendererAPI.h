#pragma once
#include "../RendererAPI.h"
#include "VulkanInstance.h"

namespace Tusk {

	class VulkanRendererAPI : public RendererAPI {
	public:
		virtual ~VulkanRendererAPI() override;

		virtual void init(const Ref<Window> window) override;
		virtual void clearScreen() override;
		virtual void drawFrame() override;

		virtual void bindShader(const Ref<Shader> shader) override;

		virtual void beginDrawing() override;
		virtual void submitToDraw(const Ref<Shader>& shader) override;
		virtual void endDrawing() override;
		/*virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		//virtual void SetClearColor(const glm::vec4 & color) = 0;
		virtual void Clear() = 0;*/

	private:
		Scope<VulkanInstance> _instance;
	};
}