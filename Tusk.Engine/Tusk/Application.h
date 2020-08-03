#pragma once

#include "Utils/Defines.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Window.h"
#include "Layers/LayerStack.h"

namespace Tusk {
	class TUSK_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = true;
		LayerStack _layerStack;
	};

	Application* createApplication();
}
