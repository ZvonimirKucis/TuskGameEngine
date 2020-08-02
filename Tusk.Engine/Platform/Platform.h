#pragma once

#include <vulkan/vulkan.h>
#include "../Utils/Types.h"

struct GLFWwindow;

namespace Tusk {

    class Engine;

    class Platform {
    public:
        Platform(Engine* engine, const char* applicationName);
        ~Platform();

        GLFWwindow* getWindow() { return _window; }

        void getRequiredExtensions(U32* extensionCount, const char*** extensionNames);

        void createSurface(VkInstance instance, VkSurfaceKHR* surface);

        const bool startGameLoop();

    private:
        GLFWwindow* _window;
        Engine* _engine;
    };
}