#pragma once

#include "Entity.h"

namespace Tusk {
	class ScriptableEntity {
	public:
		void setEntity(Entity entity) { _entity = entity; }

		template<typename T>
		T& getComponent() {
			return _entity.getComponent<T>();
		}

	private:
		Entity _entity;
	};
}
