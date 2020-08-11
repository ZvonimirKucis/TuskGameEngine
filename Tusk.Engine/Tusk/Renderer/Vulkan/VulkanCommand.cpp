#include "tuskpch.h"

#include "../../Utils/Logger.h"
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

    void VulkanCommand::submitToDraw(VkPipeline pipeline, VkPipelineLayout pipelineLayout, VkBuffer vertexBuffer, VkBuffer indexBuffer, uint32_t indicesSize, std::vector<VkDescriptorSet> descriptorSets) {
        auto swapChainExtent = _swapchain->getSwapChainExtent();
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapChainExtent;

        vkCmdBindPipeline(_commandBuffers[_currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        vkCmdSetViewport(_commandBuffers[_currentFrame], 0, 1, &viewport);
        vkCmdSetScissor(_commandBuffers[_currentFrame], 0, 1, &scissor);

        VkBuffer vertexBuffers[] = { vertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(_commandBuffers[_currentFrame], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(_commandBuffers[_currentFrame], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(_commandBuffers[_currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[_currentFrame], 0, nullptr);

        vkCmdDrawIndexed(_commandBuffers[_currentFrame], indicesSize, 1, 0, 0, 0);
	}

    void VulkanCommand::endDrawing() {
        vkCmdEndRenderPass(_commandBuffers[_currentFrame]);
        VK_CHECK(vkEndCommandBuffer(_commandBuffers[_currentFrame]))

       _currentFrame = (_currentFrame + 1) % 3;
    }

    VkCommandBuffer VulkanCommand::beginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = _commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(_device->getDevice(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void VulkanCommand::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(_device->getGraphicsQueue() , 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(_device->getGraphicsQueue());

        vkFreeCommandBuffers(_device->getDevice(), _commandPool, 1, &commandBuffer);
    }

	VulkanCommand::~VulkanCommand() {
        vkFreeCommandBuffers(_device->getDevice(), _commandPool, static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
		vkDestroyCommandPool(_device->getDevice(), _commandPool, nullptr);
	}
}