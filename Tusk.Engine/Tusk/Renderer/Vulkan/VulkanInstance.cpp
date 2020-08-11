#include "tuskpch.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../Utils/Logger.h"
#include "VulkanUtils.h"
#include "VulkanInstance.h"
#include "VulkanBuffer.h"
#include "../../Platform/Window.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

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
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
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
        auto swapChainImages = _swapchain->getSwapChainImageViews();
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            vkDestroyBuffer(_device->getDevice(), _uniformBuffers[i], nullptr);
            vkFreeMemory(_device->getDevice(), _uniformBuffersMemory[i], nullptr);
        }

        vkDestroyDescriptorPool(_device->getDevice(), _descriptorPool, nullptr);

        delete _framebuffer;
        delete _command;
        delete _swapchain;
    }

    void VulkanInstance::recreateSwapChain() {
        vkDeviceWaitIdle(_device->getDevice());
        cleanupSwapChain();

        createSwapChain();
        createFramebuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommand();
    }

    void VulkanInstance::createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);
        auto swapChainImages = _swapchain->getSwapChainImageViews();

        _uniformBuffers.resize(swapChainImages.size());
        _uniformBuffersMemory.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VulkanBufferHelper::createBuffer(_device, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
        }
    }

    void VulkanInstance::createDescriptorPool() {
        auto swapChainImages = _swapchain->getSwapChainImageViews();
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

        VK_CHECK(vkCreateDescriptorPool(_device->getDevice(), &poolInfo, nullptr, &_descriptorPool))
    }

    void VulkanInstance::createDescriptorSets() {
        auto swapChainImages = _swapchain->getSwapChainImageViews();

        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), _pipeline->getDescriptorSetLayout());
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = _descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
        allocInfo.pSetLayouts = layouts.data();

        _descriptorSets.resize(swapChainImages.size());
        if (vkAllocateDescriptorSets(_device->getDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = _uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = _descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(_device->getDevice(), 1, &descriptorWrite, 0, nullptr);
        }
    }

    void VulkanInstance::bindIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        indexBuffer->bind(_device, _command);
        _indexBuffer = indexBuffer;
    }

    void VulkanInstance::bindVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        vertexBuffer->bind(_device, _command);
        _vertexBuffer = vertexBuffer;
    }

    void VulkanInstance::bindShader(const Ref<Shader> shader) {
        shader->createShaderModules(_device, _swapchain, _pipeline);
        _command->submitToDraw(shader->getGraphicsPipeline(), _pipeline->getPipelineLayout(), _vertexBuffer->getBuffer(), _indexBuffer->getBuffer(), _indexBuffer->getCount(), _descriptorSets);
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

        updateUniformBuffer(imageIndex);

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

    void VulkanInstance::updateUniformBuffer(uint32_t currentImage) {
        auto swapChainExtent = _swapchain->getSwapChainExtent();
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
        ubo.proj[1][1] *= -1;

        void* data;
        vkMapMemory(_device->getDevice(), _uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(_device->getDevice(), _uniformBuffersMemory[currentImage]);
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

        vkDestroyBuffer(_device->getDevice(), _indexBuffer->getBuffer(), nullptr);
        vkFreeMemory(_device->getDevice(), _indexBuffer->getMemory(), nullptr);

        vkDestroyBuffer(_device->getDevice(), _vertexBuffer->getBuffer(), nullptr);
        vkFreeMemory(_device->getDevice(), _vertexBuffer->getMemory(), nullptr);

        cleanupSwapChain();

        delete _pipeline;
        delete _device;

        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }
}