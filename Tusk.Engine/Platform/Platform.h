#pragma once

#include "../Utils/Types.h"

struct GLFWwindow;

namespace Tusk {

    class Engine;

    class Platform {
    public:
        Platform(Engine* engine, const char* applicationName);
        ~Platform();

        GLFWwindow* GetWindow() { return _window; }

        void GetRequiredExtensions(U32* extensionCount, const char*** extensionNames);

        const bool StartGameLoop();
    private:
        GLFWwindow* _window;
        Engine* _engine;
    };
}