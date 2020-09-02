#pragma once

#include "Tusk/Model/Model.h"
#include "Tusk/Model/AnimationModel.h"
#include "Tusk/Model/Material.h"

#include "Tusk/Light/DirectionalLight.h"
#include "Tusk/Light/LightObject.h"

#include "Tusk/Camera/SceneCamera.h"

#include "Tusk/Audio/AudioSource.h"

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
		Ref<Material> material;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const Ref<Model> model, const Ref<Material> material)
			: model(model), material(material) {}
	};

	struct AnimatedMeshComponent {
		Ref<AnimationModel> model;
		Ref<Material> material;

		AnimatedMeshComponent() = default;
		AnimatedMeshComponent(const AnimatedMeshComponent&) = default;
		AnimatedMeshComponent(const Ref<AnimationModel> model, const Ref<Material> material)
			: model(model), material(material) {}
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

	struct AudioSourceComponent {
		Ref<AudioSource> source;

		AudioSourceComponent() = default;
		AudioSourceComponent(const AudioSourceComponent&) = default;
		AudioSourceComponent(const Ref<AudioSource>& source)
			:source(source) {}

	};
}
