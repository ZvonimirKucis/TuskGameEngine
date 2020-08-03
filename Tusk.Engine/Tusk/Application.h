#pragma once

#include "Utils/Defines.h"
#include "Events/Event.h"
#include "Platform/Window.h"

namespace Tusk {
	class TUSK_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
	};

	Application* createApplication();
}
