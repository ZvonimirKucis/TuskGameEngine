#include "tuskpch.h"

#include "Application.h"
#include "Renderer/Renderer.h"


namespace Tusk {
	Application* Application::_instance = nullptr;

	Application::Application(const std::string& name, uint32_t width, uint32_t height) {
		_instance = this;

		_window = Window::create(WindowCreateInfo(name, width, height));
		_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		_window->setVSync(true);

		_imGuiLayer = new ImGuiLayer();
		pushOverlay(_imGuiLayer);

		Renderer::init();
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

				_imGuiLayer->begin();
				for (Layer* layer : _layerStack) {
					layer->onImGuiRender(deltaTime);
				}
				_imGuiLayer->end();
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
		Renderer::onWindowResize(e.getWidth(), e.getHeight());
		return false;
	}

	Application::~Application() {
	}
}