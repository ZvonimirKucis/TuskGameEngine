#pragma once

#include <entt.hpp>
#include "Scene.h"

namespace Tusk {

	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& addComponent(Args&&... args) {
			return _scene->_registry.emplace<T>(_entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent() {
			return _scene->_registry.get<T>(_entityHandle);
		}

		template<typename T>
		bool hasComponent() {
			return _scene->_registry.has<T>(_entityHandle);
		}

		template<typename T>
		void removeComponent() {
			return _scene->_registry.remove<T>(_entityHandle);
		}
		
		operator bool() const { return _entityHandle != entt::null; }

	private:
		entt::entity _entityHandle{ entt::null };
		Scene* _scene = nullptr;

	};
}