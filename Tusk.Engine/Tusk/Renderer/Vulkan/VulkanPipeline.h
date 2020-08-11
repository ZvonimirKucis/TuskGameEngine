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
		VkDescriptorSetLayout getDescriptorSetLayout() { return _descriptorSetLayout; }

	private:
		void createRenderPass();
		void createDescriptorSetLayout();
		void createPipelineLayout();

	private:
		VkRenderPass _renderPass;
		VkDescriptorSetLayout _descriptorSetLayout;
		VkPipelineLayout _pipelineLayout;
		VkPipeline _graphicsPipeline;

		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
	};
}