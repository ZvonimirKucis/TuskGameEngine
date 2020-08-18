#pragma once
#include <Tusk.h>

namespace Tusk {
	class CameraController : public ScriptableEntity {
	public:
		void onCreate();
		void onDestroy();
		void onUpdate(float deltaTime);
	};
}