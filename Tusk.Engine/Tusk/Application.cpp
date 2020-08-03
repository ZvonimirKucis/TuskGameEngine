#include "tuskpch.h"

#include "Application.h"

namespace Tusk {
	Application::Application() {
		_window = std::unique_ptr<Window>(Window::create());
		_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

		Logger::Trace(e.ToString().c_str());
	}

	void Application::run() {
		while (_running) {
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