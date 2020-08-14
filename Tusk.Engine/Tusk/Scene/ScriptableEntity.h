#pragma once

#include "Entity.h"

namespace Tusk {
	class ScriptableEntity {
	public:
		template<typename T>
		T& GetComponent() {
			return _entity.getComponent<T>();
		}

	private:
		Entity _entity;
		friend class Scene;
	};
}
