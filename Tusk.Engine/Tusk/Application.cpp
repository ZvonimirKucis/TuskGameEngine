#include "tuskpch.h"

#include "Application.h"
#include "Utils/Logger.h"
#include "Renderer/Renderer.h"

namespace Tusk {
	Application* Application::_instance = nullptr;

	Application::Application() {
		_instance = this;

		_window = Window::create();
		_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		Renderer::init(_window);
	}

	void Application::pushLayer(Layer* layer) {
		_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer) {
		_layerStack.pushOverlay(layer);
	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

		for (auto it = _layerStack.end(); it != _layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	void Application::run() {
		while (_running) {

			for (Layer* layer : _layerStack) {
				layer->onUpdate();
			}
			_window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		_running = false;
		return true;
	}

	Application::~Application() {

	}
}