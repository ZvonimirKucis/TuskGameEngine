#pragma once
#include <Tusk.h>

namespace Tusk {
	class ModelController : public ScriptableEntity {
	public:
		virtual void onCreate() override;
		virtual void onDestroy() override;
		virtual void onUpdate(float deltaTime) override;
	};
}