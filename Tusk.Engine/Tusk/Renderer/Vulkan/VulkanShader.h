#pragma once

#include <vulkan/vulkan.h>
#include "../Shader.h"
#include "VulkanDevice.h"
#include "VulkanPipeline.h"
#include "VulkanSwapChain.h"
#include "VulkanVertex.h"
#include "../Buffer.h"


namespace Tusk {
	class VulkanShader : public Shader {
	public:
		VulkanShader(const std::string& vertexFile, const std::string& fragmentFile);
		virtual ~VulkanShader();

		virtual void createShaderModules(VulkanDevice* device, VulkanSwapChain* swapchain, VulkanPipeline* pipeline) override;

		virtual VkPipeline getGraphicsPipeline() override { return _graphicsPipeline; }

	private:
		std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);
		void createGraphicsPipeline();
	private:
		std::vector<char> _vertShaderCode;
		std::vector<char> _fragShaderCode;

		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;
		VkPipeline _graphicsPipeline;
		VkShaderModule _vertShaderModule = VK_NULL_HANDLE;
		VkShaderModule _fragShaderModule = VK_NULL_HANDLE;
	};
}