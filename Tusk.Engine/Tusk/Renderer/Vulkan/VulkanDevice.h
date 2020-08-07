#pragma once

#include <vulkan/vulkan.h>
#include "VulkanUtils.h"

namespace Tusk {

    class VulkanDevice {
    public:
        VulkanDevice(VkInstance instance, VkSurfaceKHR surface);
        ~VulkanDevice();

        VkDevice getDevice() { return _device; }
        VkPhysicalDevice getPhysicalDevice() { return _physicalDevice; }

        VkQueue getGraphicsQueue() { return _graphicsQueue;  }
        VkQueue getPresentationQueue() { return _presentationQueue; }
        uint32_t getGraphicsFamilyQueueIndex() { return _graphicsFamilyQueueIndex;  }
        uint32_t getPresentationFamilyQueueIndex() { return _presentationFamilyQueueIndex; }

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    private:
        void pickPhysicalDevice();
        int rateDeviceSuitability(VkPhysicalDevice device);
        void createLogicalDevice();

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void detectQueueFamilyIndices(VkPhysicalDevice physicalDevice, uint32_t* graphicsQueueIndex, uint32_t* presentationQueueIndex);

    private:
        VkInstance _instance;
        VkSurfaceKHR _surface;

        VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
        VkDevice _device;

        uint32_t _graphicsFamilyQueueIndex;
        uint32_t _presentationFamilyQueueIndex;
        VkQueue _graphicsQueue;
        VkQueue _presentationQueue;
    };
}