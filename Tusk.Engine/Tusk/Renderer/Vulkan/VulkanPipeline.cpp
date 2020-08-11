#include "tuskpch.h"

#include "../../Utils/Logger.h"

#include "VulkanPipeline.h"

namespace Tusk {

	VulkanPipeline::VulkanPipeline(VulkanDevice* device, VulkanSwapChain* swapchain)
		: _device(device), _swapchain(swapchain){
        Logger::Trace("Initializing Vulkan render pass and pipeline layout.");

        createRenderPass();
        createDescriptorSetLayout();
        createPipelineLayout();
	}

    void VulkanPipeline::createRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = _swapchain->getSwapChainImageFormat();
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        VK_CHECK(vkCreateRenderPass(_device->getDevice(), &renderPassInfo, nullptr, &_renderPass))
    }

    void VulkanPipeline::createDescriptorSetLayout() {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        VK_CHECK(vkCreateDescriptorSetLayout(_device->getDevice(), &layoutInfo, nullptr, &_descriptorSetLayout))
    }

    void VulkanPipeline::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &_descriptorSetLayout;

        VK_CHECK(vkCreatePipelineLayout(_device->getDevice(), &pipelineLayoutInfo, nullptr, &_pipelineLayout))
    }

	VulkanPipeline::~VulkanPipeline() {
        vkDestroyDescriptorSetLayout(_device->getDevice(), _descriptorSetLayout, nullptr);
		vkDestroyPipelineLayout(_device->getDevice(), _pipelineLayout, nullptr);
        vkDestroyRenderPass(_device->getDevice(), _renderPass, nullptr);
	}
}