#include "tuskpch.h"

#include "Application.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

namespace Tusk {
	Application* Application::_instance = nullptr;

	Application::Application() {
		_instance = this;

		_window = Window::create();
		_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		//Renderer::init(_window);
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
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));

		for (auto it = _layerStack.end(); it != _layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.handled) {
				break;
			}
		}
	}

	void Application::run() {
		while (_running) {
			auto time = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = time - _lastFrameTime;
			float deltaTime = elapsed_seconds.count();
			_lastFrameTime = time;

			if (!_minimized) {
				for (Layer* layer : _layerStack) {
					layer->onUpdate(deltaTime);
				}
				//Renderer::update();
			}

			_window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		_running = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e) {
		if (e.getWidth() == 0 || e.getHeight() == 0){
			_minimized = true;
			return false;
		}
		_minimized = false;
		//Renderer::onWindowResize();
		return false;
	}

	Application::~Application() {

	}
}