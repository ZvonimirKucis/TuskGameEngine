#pragma once

#include "../Model/Mesh.h"
#include "../Model/Material.h"

#include "ScriptableEntity.h"
#include "Transform.h"

#include <string>

namespace Tusk {

	struct TagComponent {
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}
	};

	struct TransformComponent {
		Transform transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Transform& transform)
			: transform(transform) {}

	};

	struct MeshComponent {
		Mesh* mesh;
		Material* material;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(Mesh* mesh)
			: mesh(mesh) {}
		MeshComponent(Mesh* mesh, Material* material)
			: mesh(mesh), material(material) {}
	};

	struct ScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		std::function<void()> instantiateFunction;
		std::function<void()> destroyInstanceFunction;

		std::function<void(ScriptableEntity*)> onCreateFunction;
		std::function<void(ScriptableEntity*)> onDestroyFunction;
		std::function<void(ScriptableEntity*, float)> onUpdateFunction;

		template<typename T>
		void Bind()
		{
			instantiateFunction = [&]() { instance = new T(); };
			destroyInstanceFunction = [&]() { delete (T*)instance; instance = nullptr; };

			onCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->onCreate(); };
			onDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->onDestroy(); };
			onUpdateFunction = [](ScriptableEntity* instance, float deltaTime) { ((T*)instance)->onUpdate(deltaTime); };
		}	
	};

	/*struct CameraComponent {
		bool primary = true;
	};*/
}
