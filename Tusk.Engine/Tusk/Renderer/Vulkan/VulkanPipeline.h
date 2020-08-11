#pragma once

#include <vulkan/vulkan.h>
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

namespace Tusk {

	class VulkanPipeline {
	public:
		VulkanPipeline(VulkanDevice* device, VulkanSwapChain* swapchain);
		~VulkanPipeline();

		VkRenderPass getRenderPass() { return _renderPass; }
		VkPipelineLayout getPipelineLayout() { return _pipelineLayout; }

	private:
		void createRenderPass();
		void createPipelineLayout();

	private:
		VkRenderPass _renderPass;
		VkPipelineLayout _pipelineLayout;
		VkPipeline _graphicsPipeline;

		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
	};
}