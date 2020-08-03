#pragma once

#include <vulkan/vulkan.h>

namespace Tusk {
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanDevice {
    public:
        VulkanDevice(VkInstance instance, VkSurfaceKHR surface);
        ~VulkanDevice();

        VkDevice getDevice() { return _device; }

        VkPhysicalDevice getPhysicalDevice() { return _physicalDevice; }

        VkQueue getGraphicsQueue() { return _graphicsQueue;  }

        VkQueue getPresentationQueue() { return _presentationQueue; }

    private:
        void pickPhysicalDevice();
        int rateDeviceSuitability(VkPhysicalDevice device);
        void createLogicalDevice();

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        void detectQueueFamilyIndices(VkPhysicalDevice physicalDevice, I32* graphicsQueueIndex, I32* presentationQueueIndex);

    private:
        VkInstance _instance;
        VkSurfaceKHR _surface;

        VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
        VkDevice _device;

        I32 _graphicsFamilyQueueIndex;
        I32 _presentationFamilyQueueIndex;
        VkQueue _graphicsQueue;
        VkQueue _presentationQueue;
    };
}