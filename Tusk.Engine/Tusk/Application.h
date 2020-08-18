#pragma once

#include "Utils/Defines.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Window.h"
#include "Layers/LayerStack.h"
#include "GUI/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Tusk {
	class Application {
	public:
		Application(const std::string& name = "Tusk Demo", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline Window& getWindow() { return *_window; }

		inline static Application& get() { return *_instance; }
	private:
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

	private:
		Ref<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		bool _minimized = false;

		std::chrono::system_clock::time_point _lastFrameTime = std::chrono::system_clock::now();

		LayerStack _layerStack;

	private:
		friend int ::main(int argc, char** argv);
		static Application* _instance;
	};

	Application* createApplication();
}
