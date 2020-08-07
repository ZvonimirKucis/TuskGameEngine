#pragma once
#include <vulkan/vulkan.h>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"
#include "VulkanFramebuffer.h"

namespace Tusk {

	class VulkanCommand {
	public:
		VulkanCommand(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline, VulkanFramebuffer* framebuffer);
		~VulkanCommand();

		void clearScreen(VkClearValue color = { 0.0f, 0.0f, 0.0f, 1.0f });

		void beginDrawing();
		void submitToDraw(VkPipeline pipeline);
		void endDrawing();

		std::vector<VkCommandBuffer> getCommandBuffers() { return _commandBuffers; }

	private:
		void createCommandPool();
	private:
		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;
		VulkanFramebuffer* _framebuffer;

		VkCommandPool _commandPool;
		std::vector<VkCommandBuffer> _commandBuffers;
		size_t _currentFrame = 0;
	};
}