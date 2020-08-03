#include "tuskpch.h"

#include "Application.h"

namespace Tusk {
	Application::Application() {
		_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application() {

	}

	void Application::run() {
		while (_running) {
			_window->onUpdate();
		}
	}
}