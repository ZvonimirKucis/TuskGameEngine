#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"
#include "VulkanShader.h"
#include "VulkanFramebuffer.h"
#include "VulkanCommand.h"
#include "VulkanTexture.h"
#include "VulkanDepthBuffer.h"

namespace Tusk {
	
	class Window;

	class VulkanDevice;
	class VulkanSwapChain;

	class VulkanInstance {
	public:
		VulkanInstance(const Ref<Window> window);
		~VulkanInstance();

		void bindIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
		void bindVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void bindShader(const Ref<Shader> shader);
		void bindTexture(const Ref<Texture>& texture);

		void clearScreen();
		void beginDrawing();
		void submitToDraw(const Ref<Shader>& shader);
		void endDrawing();
		void drawFrame();
		void setFramebufferResized() { _framebufferResized = true; }
	
	private:
		void initVulkan();
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void createDevice();
		void createSwapChain();
		void createPipeline();
		void createDepthBuffer();
		void createFramebuffer();
		void createUniformBuffers();
		void createDescriptorPool();
		void createDescriptorSets();
		void createCommand();

		void recreateSwapChain();
		void cleanupSwapChain();
		void updateUniformBuffer(uint32_t currentImage);

		std::vector<const char*> getRequiredExtensions();
		void checkValidationLayerSupport();
		void createSyncObjects();

	private:
		const int MAX_FRAMES_IN_FLIGHT = 2;

		Ref<Window> _window;
		Ref<VertexBuffer> _vertexBuffer;
		Ref<IndexBuffer> _indexBuffer;
		Ref<Texture> _texture;

		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;

		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;
		VulkanFramebuffer* _framebuffer;
		VulkanCommand* _command;
		VulkanDepthBuffer* _depthBuffer;

		uint32_t _imageIndex;
		size_t _currentFrame = 0;
		bool _framebufferResized = false;

		std::vector<VkSemaphore> _imageAvailableSemaphores;
		std::vector<VkSemaphore> _renderFinishedSemaphores;
		std::vector<VkFence> _inFlightFences;
		std::vector<VkFence> _imagesInFlight;

		std::vector<VkBuffer> _uniformBuffers;
		std::vector<VkDeviceMemory> _uniformBuffersMemory;

		VkDescriptorPool _descriptorPool;
		std::vector<VkDescriptorSet> _descriptorSets;
	};
}