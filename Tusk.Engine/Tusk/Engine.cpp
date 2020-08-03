#include "Utils/Logger.h"
#include "Platform/Platform.h"
#include "Renderer/VulkanRenderer.h"
#include "Engine.h"

namespace Tusk {
    Engine::Engine(const char* applicationName) {
        Logger::Trace("Initializing engine...");
        _platform = new Platform(this, applicationName);
        _renderer = new VulkanRenderer(_platform);
    }

    Engine::~Engine() {
        delete _renderer;
        delete _platform;
    }

    void Engine::run() {
        _platform->startGameLoop();
    }

    void Engine::onLoop(const F32 deltaTime) {

    }
}