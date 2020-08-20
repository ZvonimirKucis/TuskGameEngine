#pragma once

#include "Tusk/Model/Model.h"
#include "Tusk/Light/DirectionalLight.h"
#include "Tusk/Light/LightObject.h"
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
		Transform transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Transform& transform)
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

		ScriptableEntity* (*instantiateScript)();
		void (*destroyScript)(ScriptComponent*);

		template<typename T>
		void bind() {
			instantiateScript = []() {return static_cast<ScriptableEntity*> (new T()); };
			destroyScript = [](ScriptComponent* sc) {delete sc->instance; };
		}
	};

	struct CameraComponent {
		SceneCamera camera;
		bool primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct PointLightComponent {
		LightObject lightObject;

		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;

		LightObject* getRef() {
			return &lightObject;
		}
	};

	struct DirectionalLightComponent {
		DirectionalLight lightData;

		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(const DirectionalLight& lightData)
			:lightData(lightData) {}
		
	};
}
