#pragma once

#include "Utils/Defines.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Window.h"
#include "Layers/LayerStack.h"
#include "Renderer/Shader.h"
#include "GUI/ImGuiLayer.h"
#include "Model/Model.h"

namespace Tusk {
	class Application {
	public:
		Application();
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

		Scope<Model> _model;
		Ref<Shader> _shader;

		static Application* _instance;

		Ref<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		bool _minimized = false;

		std::chrono::system_clock::time_point _lastFrameTime = std::chrono::system_clock::now();

		LayerStack _layerStack;
	};

	Application* createApplication();
}
