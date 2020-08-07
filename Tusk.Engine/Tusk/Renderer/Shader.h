#pragma once

#include <string>
#include <vulkan/vulkan.h>

namespace Tusk {
	
	class VulkanDevice;
	class VulkanSwapChain;
	class VulkanPipeline;

	class Shader {
	public:
		virtual ~Shader() {}

		static Ref<Shader> create(const std::string& vertexFile, const std::string& fragmentFile);

		virtual void createShaderModules(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline) = 0;

		virtual VkPipeline getGraphicsPipeline() = 0;
	};
}