#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"
#include "VulkanShader.h"
#include "VulkanFramebuffer.h"
#include "VulkanCommand.h"

namespace Tusk {
	
	class Window;

	class VulkanDevice;
	class VulkanSwapChain;

	class VulkanInstance {
	public:
		VulkanInstance(const Ref<Window> window);
		~VulkanInstance();

		void bindVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void bindShader(const Ref<Shader> shader);

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
		void createFramebuffer();
		void createCommand();

		void recreateSwapChain();
		void cleanupSwapChain(); 

		std::vector<const char*> getRequiredExtensions();
		void checkValidationLayerSupport();
		void createSyncObjects();

	private:
		const int MAX_FRAMES_IN_FLIGHT = 2;

		Ref<Window> _window;
		Ref<VertexBuffer> _vertexBuffer;
		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;
		VkSurfaceKHR _surface;

		VulkanDevice* _device;
		VulkanSwapChain* _swapchain;
		VulkanPipeline* _pipeline;
		VulkanFramebuffer* _framebuffer;
		VulkanCommand* _command;

		uint32_t _imageIndex;
		size_t _currentFrame = 0;
		bool _framebufferResized = false;

		std::vector<VkSemaphore> _imageAvailableSemaphores;
		std::vector<VkSemaphore> _renderFinishedSemaphores;
		std::vector<VkFence> _inFlightFences;
		std::vector<VkFence> _imagesInFlight;
	};
}