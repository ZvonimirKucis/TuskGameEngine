#pragma once

#include "Tusk/Model/Model.h"
#include "Tusk/Camera/SceneCamera.h"
#include "Tusk/Renderer/Shader.h"

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
		glm::mat4 transform{1.0f};

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: transform(transform) {}

	};

	struct MeshComponent {
		Ref<Model> model;
		Ref<Shader> shader;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const Ref<Model> model, const Ref<Shader> shader)
			: model(model), shader(shader) {}
	};

	struct ScriptComponent {
		ScriptableEntity* Instance = nullptr;

		std::function<void()> instantiateFunction;
		std::function<void()> destroyInstanceFunction;

		std::function<void(ScriptableEntity*)> onCreateFunction;
		std::function<void(ScriptableEntity*)> onDestroyFunction;
		std::function<void(ScriptableEntity*, float)> onUpdateFunction;

		template<typename T>
		void bind()
		{
			instantiateFunction = [&]() { Instance = new T(); };
			destroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };

			onCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->onCreate(); };
			onDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->onDestroy(); };
			onUpdateFunction = [](ScriptableEntity* instance, float deltaTime) { ((T*)instance)->onUpdate(deltaTime); };
		}	
	};

	struct CameraComponent {
		SceneCamera Camera;
		bool primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
