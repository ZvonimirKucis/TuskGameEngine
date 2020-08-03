#include "tuskpch.h"

#include "VulkanUtils.h"
#include "VulkanDevice.h"

namespace Tusk {
    std::vector<const char*> requiredExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VulkanDevice::VulkanDevice(VkInstance instance, VkSurfaceKHR surface) {
        _instance = instance;
        _surface = surface;

        Logger::Trace("Initializing device...");
        pickPhysicalDevice();
        createLogicalDevice();
    }

    void VulkanDevice::pickPhysicalDevice() {
        U32 deviceCount = 0;
        vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            Logger::Fatal("Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;
        for (const auto& device : devices) {
            int score = rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if (candidates.rbegin()->first > 0) {
            _physicalDevice = candidates.rbegin()->second;
        }

        if (_physicalDevice == VK_NULL_HANDLE) {
            Logger::Fatal("Failed to find a suitable GPU!");
        }
    }

    void VulkanDevice::createLogicalDevice() {
        I32 graphicsQueueIndex = -1;
        I32 presentationQueueIndex = -1;
        detectQueueFamilyIndices(_physicalDevice, &graphicsQueueIndex, &presentationQueueIndex);

        bool presentationSharesGraphicsQueue = graphicsQueueIndex == presentationQueueIndex;

        std::vector<U32> indices;
        indices.push_back(graphicsQueueIndex);
        if (!presentationSharesGraphicsQueue) {
            indices.push_back(presentationQueueIndex);
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(indices.size());
        for (U32 i = 0; i < (U32)indices.size(); ++i) {
            queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfos[i].queueFamilyIndex = indices[i];
            queueCreateInfos[i].queueCount = 1;
            queueCreateInfos[i].flags = 0;
            queueCreateInfos[i].pNext = nullptr;
            F32 queuePriority = 1.0f;
            queueCreateInfos[i].pQueuePriorities = &queuePriority;
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = (U32)indices.size();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = (U32)requiredExtensions.size();
        createInfo.pNext = nullptr;
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        if (ENABLE_VALIDATION_LAYERS) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(requiredValidationLayers.size());
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        VK_CHECK(vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device));

        _graphicsFamilyQueueIndex = graphicsQueueIndex;
        _presentationFamilyQueueIndex = presentationQueueIndex;

        vkGetDeviceQueue(_device, _graphicsFamilyQueueIndex, 0, &_graphicsQueue);
        vkGetDeviceQueue(_device, _presentationFamilyQueueIndex, 0, &_presentationQueue);
    }

    int VulkanDevice::rateDeviceSuitability(VkPhysicalDevice device) {
        I32 graphicsQueueIndex = -1;
        I32 presentationQueueIndex = -1;
        detectQueueFamilyIndices(device, &graphicsQueueIndex, &presentationQueueIndex);
        bool supportsRequiredQueueFamilies = (graphicsQueueIndex != -1) && (presentationQueueIndex != -1);

        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(device, &features);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        int score = 0;
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 1000;
        }
        score += properties.limits.maxImageDimension2D;
        
        bool condition = supportsRequiredQueueFamilies && extensionsSupported && swapChainAdequate && features.samplerAnisotropy;
        return condition ? score : 0;
    }

    bool VulkanDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(requiredExtensions.begin(), requiredExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    SwapChainSupportDetails VulkanDevice::querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    void VulkanDevice::detectQueueFamilyIndices(VkPhysicalDevice physicalDevice, I32* graphicsQueueIndex, I32* presentationQueueIndex) {
        U32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> familyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, familyProperties.data());

        for (U32 i = 0; i < queueFamilyCount; ++i) {

            if (familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                *graphicsQueueIndex = i;
            }

            VkBool32 supportsPresentation = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, _surface, &supportsPresentation);
            if (supportsPresentation) {
                *presentationQueueIndex = i;
            }
        }
    }

    VulkanDevice::~VulkanDevice() {
        vkDestroyDevice(_device, nullptr);
    }
}