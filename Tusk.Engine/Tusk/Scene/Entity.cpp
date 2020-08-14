#include "tuskpch.h"

#include "Entity.h"

namespace Tusk {
	Entity::Entity(entt::entity handle, Scene* scene)
		: _entityHandle(handle), _scene(scene) {}
}