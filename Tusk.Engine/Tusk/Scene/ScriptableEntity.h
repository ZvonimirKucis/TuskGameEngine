#pragma once

#include "Entity.h"

namespace Tusk {
	class ScriptableEntity {
	public:
		virtual void onCreate() = 0;;
		virtual void onDestroy() = 0;
		virtual void onUpdate(float deltaTime) = 0;

		template<typename T>
		T& getComponent() {
			return _entity->getComponent<T>();
		}

	private:
		Entity* _entity = nullptr;
		friend class Scene;
	};
}
