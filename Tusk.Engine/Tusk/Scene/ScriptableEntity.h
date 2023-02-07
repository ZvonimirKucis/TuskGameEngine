#pragma once

#include "Entity.h"

namespace Tusk {
	class ScriptableEntity {
	public:
		template<typename T>
		T& getComponent() {
			return _entity.getComponent<T>();
		}

	protected:
		virtual void onCreate() {}
		virtual void onDestroy() {}
		virtual void onUpdate(float deltaTime) {}

	private:
		Entity _entity;
		friend class Scene;
	};
}
