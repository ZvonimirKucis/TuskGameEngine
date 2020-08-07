#include "tuskpch.h"

#include "../../Utils/Logger.h"#
#include "VulkanCommand.h"

namespace Tusk {

	VulkanCommand::VulkanCommand(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline, VulkanFramebuffer* framebuffer)
		: _device(device), _swapchain(swapchain), _pipeline(pipeline), _framebuffer(framebuffer){
		Logger::Trace("Initializing Vulkan command pool.");
		createCommandPool();
	}

    void VulkanCommand::createCommandPool() {
        _commandBuffers.resize(_framebuffer->getSwapChainFramebuffers().size());
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = _device->getGraphicsFamilyQueueIndex();
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // Optiona

        VK_CHECK(vkCreateCommandPool(_device->getDevice(), &poolInfo, nullptr, &_commandPool))
        
        VkCommandBufferAllocateInfo allocInfo {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = _commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)_commandBuffers.size();

        VK_CHECK(vkAllocateCommandBuffers(_device->getDevice(), &allocInfo, _commandBuffers.data()))
        
    }

    void VulkanCommand::beginDrawing() {
        VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        VK_CHECK(vkBeginCommandBuffer(_commandBuffers[_currentFrame], &beginInfo))
    }

    void VulkanCommand::clearScreen(VkClearValue color) {
        auto swapChainFramebuffers = _framebuffer->getSwapChainFramebuffers();
        auto renderPass = _pipeline->getRenderPass();

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass;
        renderPassInfo.framebuffer = swapChainFramebuffers[_currentFrame];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = _swapchain->getSwapChainExtent();

        VkClearValue clearColor = color;
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(_commandBuffers[_currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanCommand::submitToDraw(VkPipeline pipeline) {
        vkCmdBindPipeline(_commandBuffers[_currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        vkCmdDraw(_commandBuffers[_currentFrame], 3, 1, 0, 0);
	}

    void VulkanCommand::endDrawing() {
        vkCmdEndRenderPass(_commandBuffers[_currentFrame]);
        VK_CHECK(vkEndCommandBuffer(_commandBuffers[_currentFrame]))

       _currentFrame = (_currentFrame + 1) % 3;
    }

	VulkanCommand::~VulkanCommand() {
		vkDestroyCommandPool(_device->getDevice(), _commandPool, nullptr);
	}
}