#pragma once

#include "utils/types.h"

namespace Tusk {

    class Platform;
    class VulkanRenderer;

    class Engine {
    public:
        Engine(const char* applicationName);
        ~Engine();

        void Run();

        void OnLoop(const F32 deltaTime);
    private:
        Platform* _platform;
        VulkanRenderer* _renderer;
    };
}