#include "tuskpch.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../Utils/Logger.h"
#include "VulkanUtils.h"
#include "VulkanInstance.h"
#include "../../Platform/Window.h"

namespace Tusk {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

        switch (messageSeverity) {
        default:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            Logger::Error(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            Logger::Warn(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            Logger::Log(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            Logger::Trace(pCallbackData->pMessage);
            break;
        }

        return VK_FALSE;
    }

    VulkanInstance::VulkanInstance(const Ref<Window> window) {
        _window = window;

        Logger::Trace("Initializing Vulkan renderer.");
        initVulkan();
    }

    void VulkanInstance::initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        createDevice();
        createSwapChain();
        createPipeline();
        createFramebuffer();
        createCommand();
        createSyncObjects();
    }

    void VulkanInstance::createInstance() {
        VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
        appInfo.apiVersion = VK_API_VERSION_1_2;
        appInfo.pApplicationName = "VulkanEngine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        createInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (ENABLE_VALIDATION_LAYERS) {
            checkValidationLayerSupport();
            createInfo.enabledLayerCount = static_cast<uint32_t>(requiredValidationLayers.size());
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &_instance));
    }

    void VulkanInstance::setupDebugMessenger() {
        if (!ENABLE_VALIDATION_LAYERS) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = this;

        PFN_vkCreateDebugUtilsMessengerEXT createFunction = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
        ASSERT_MSG(createFunction, "Failed to create debug messenger!");
        createFunction(_instance, &createInfo, nullptr, &_debugMessenger);
    }

    void VulkanInstance::createSurface() {
        Logger::Trace("Creating Vulkan surface.");
        VK_CHECK(glfwCreateWindowSurface(_instance,(GLFWwindow*) _window->getNativeWindow(), nullptr, &_surface))
    }

    void VulkanInstance::createDevice() {
        _device = new VulkanDevice(_instance, _surface);
    }

    void VulkanInstance::createSwapChain() {
        _swapchain = new VulkanSwapChain(_device, _window, _surface);
    }

    void VulkanInstance::createPipeline() {
        _pipeline = new VulkanPipeline(_device, _swapchain);
    }

    void VulkanInstance::createFramebuffer() {
        _framebuffer = new VulkanFramebuffer(_device, _swapchain, _pipeline);
    }

    void VulkanInstance::createCommand() {
        _command = new VulkanCommand(_device, _swapchain, _pipeline, _framebuffer);
    }

    void VulkanInstance::cleanupSwapChain() {
        delete _framebuffer;
        delete _command;
        delete _swapchain;
    }

    void VulkanInstance::recreateSwapChain() {
        vkDeviceWaitIdle(_device->getDevice());
        cleanupSwapChain();

        createSwapChain();
        createFramebuffer();
        createCommand();
    }

    void VulkanInstance::bindVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        vertexBuffer->bind(_device);
        _vertexBuffer = vertexBuffer;
    }

    void VulkanInstance::bindShader(const Ref<Shader> shader) {
        shader->createShaderModules(_device, _swapchain, _pipeline);
        _command->submitToDraw(shader->getGraphicsPipeline(), _vertexBuffer->getBuffer());
    }

    void VulkanInstance::beginDrawing() {
        _command->beginDrawing();
    }

    void VulkanInstance::submitToDraw(const Ref<Shader>& shader) {
  
    }

    void VulkanInstance::endDrawing() {
        _command->endDrawing();
    }

    void VulkanInstance::clearScreen() {
        _command->clearScreen();
    }

    void VulkanInstance::drawFrame() {
        vkWaitForFences(_device->getDevice(), 1, &_inFlightFences[_currentFrame], VK_TRUE, UINT64_MAX);
        auto commandBuffers = _command->getCommandBuffers();

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(_device->getDevice(), _swapchain->getSwapChain(), UINT64_MAX, _imageAvailableSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            Logger::Fatal("Failed to acquire  swap chain image!");
        }

        if (_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(_device->getDevice(), 1, &_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        _imagesInFlight[imageIndex] = _inFlightFences[_currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { _imageAvailableSemaphores[_currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
        
        VkSemaphore signalSemaphores[] = { _renderFinishedSemaphores[_currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(_device->getDevice(), 1, &_inFlightFences[_currentFrame]);

        VK_CHECK(vkQueueSubmit(_device->getGraphicsQueue(), 1, &submitInfo, _inFlightFences[_currentFrame]))

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { _swapchain->getSwapChain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(_device->getPresentationQueue(), &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized) {
            _framebufferResized = false;
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            Logger::Fatal("Failed to present swap chain image!");
        }

        _currentFrame = (_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    std::vector<const char*> VulkanInstance::getRequiredExtensions() {
        unsigned int glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if (ENABLE_VALIDATION_LAYERS) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void VulkanInstance::checkValidationLayerSupport() {
        unsigned int layerCount;
        VK_CHECK(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));
        std::vector<VkLayerProperties> availableLayers(layerCount);
        VK_CHECK(vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data()));

        for (const char* layerName : requiredValidationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                Logger::Fatal("Validation layer is missing: %s.", layerName);
            }
        }
    }

    void VulkanInstance::createSyncObjects() {
        _imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        _renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        _inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        _imagesInFlight.resize(_swapchain->getSwapChainImageViews().size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
        VkFenceCreateInfo fenceInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            VK_CHECK(vkCreateSemaphore(_device->getDevice(), &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]))
            VK_CHECK(vkCreateSemaphore(_device->getDevice(), &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]))
            VK_CHECK(vkCreateFence(_device->getDevice(), &fenceInfo, nullptr, &_inFlightFences[i]))
        }
    }

    VulkanInstance::~VulkanInstance() {
        vkDeviceWaitIdle(_device->getDevice());

        if (ENABLE_VALIDATION_LAYERS) {
            PFN_vkDestroyDebugUtilsMessengerEXT destroyFunction = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
            destroyFunction(_instance, _debugMessenger, nullptr);
        }

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(_device->getDevice(), _renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(_device->getDevice(), _imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(_device->getDevice(), _inFlightFences[i], nullptr);
        }
        vkDestroyBuffer(_device->getDevice(), _vertexBuffer->getBuffer(), nullptr);
        vkFreeMemory(_device->getDevice(), _vertexBuffer->getMemory(), nullptr);

        delete _framebuffer;
        delete _command;
        delete _pipeline;
        delete _swapchain;
        delete _device;

        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }
}