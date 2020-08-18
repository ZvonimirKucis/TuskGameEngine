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
		ScriptableEntity* instance = nullptr;

		template<typename T>
		void bind() {
			instance = new T();
		}
	};

	struct CameraComponent {
		SceneCamera Camera;
		bool primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
