#include <cstring>

#include "../Utils/Logger.h"
#include "../Platform/Platform.h"
#include "VulkanUtils.h"
#include "VulkanDevice.h"
#include "VulkanRenderer.h"

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

    VulkanRenderer::VulkanRenderer(Platform* platform) {
        _platform = platform;

        Logger::Trace("Initializing Vulkan renderer...");
        initVulkan();
    }

    void VulkanRenderer::initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        createDevice();
    }

    void VulkanRenderer::createInstance() {
        VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
        appInfo.apiVersion = VK_API_VERSION_1_2;
        appInfo.pApplicationName = "VulkanEngine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        createInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<U32>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (ENABLE_VALIDATION_LAYERS) {
            checkValidationLayerSupport();
            createInfo.enabledLayerCount = static_cast<U32>(requiredValidationLayers.size());
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &_instance));
    }

    void VulkanRenderer::setupDebugMessenger() {
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

    void VulkanRenderer::createSurface() {
        _platform->createSurface(_instance, &_surface);
    }

    void VulkanRenderer::createDevice() {
        _device = new VulkanDevice(_instance, _surface);
    }

    std::vector<const char*> VulkanRenderer::getRequiredExtensions() {
        U32 glfwExtensionCount = 0;
        const char** glfwExtensions;
        _platform->getRequiredExtensions(&glfwExtensionCount, &glfwExtensions);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (ENABLE_VALIDATION_LAYERS) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void VulkanRenderer::checkValidationLayerSupport() {
        U32 layerCount;
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

    VulkanRenderer::~VulkanRenderer() {
        if (ENABLE_VALIDATION_LAYERS) {
            PFN_vkDestroyDebugUtilsMessengerEXT destroyFunction = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
            destroyFunction(_instance, _debugMessenger, nullptr);
        }

        delete _device;

        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }
}