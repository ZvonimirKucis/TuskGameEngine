#pragma once

#include "Utils/Defines.h"

namespace Tusk {
	class TUSK_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}
