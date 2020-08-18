#pragma once
#include <Tusk.h>

namespace Tusk {
	class ModelController : public ScriptableEntity {
	public:
		void onCreate();
		void onDestroy();
		void onUpdate(float deltaTime);
	};
}