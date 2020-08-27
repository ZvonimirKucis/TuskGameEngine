#include "tuskpch.h"	

#include "Tusk/Renderer/Renderer.h"

#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace Tusk {

	Scene::Scene() {}

	Entity Scene::createEntity(const std::string& name) {
		Entity entity =  {_registry.create(), this};
		entity.addComponent<TransformComponent>();
		
		auto& tag = entity.addComponent<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::startScene() {
		// Create scripts
		{
			auto view = _registry.view<ScriptComponent>();
			for (auto entity : view) {
				auto& script = view.get<ScriptComponent>(entity);
				script.instance = script.instantiateScript();
				script.instance->_entity = Entity(entity, this);
				script.instance->onCreate();
			}
		}

		// Get directional light data
		{
			auto view = _registry.view<DirectionalLightComponent>();
			for (auto entity : view) {
				auto& light = view.get<DirectionalLightComponent>(entity);
				_lightData = light.lightData;
				break;
			}
		}
	}

	void Scene::onUpdate(float deltaTime) {
		// Update scripts
		{
			auto view = _registry.view<ScriptComponent>();
			for (auto entity : view) {
				auto& script = view.get<ScriptComponent>(entity);
				script.instance->onUpdate(deltaTime);
				
			}
		}

		// Find primary camera
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = _registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.primary)
				{
					mainCamera = &camera.camera;
					cameraTransform = &transform.transform.getModelMatrix();
					break;
				}
			}
		}

		// Render
		if(mainCamera) {
			Renderer::beginScene(*mainCamera, *cameraTransform, _lightData);
			// Lights
			if(_renderLights) {
				auto view = _registry.view<TransformComponent, PointLightComponent>();
				for (auto entity : view) {
					auto [transform, light] = view.get<TransformComponent, PointLightComponent>(entity);
					Renderer::submit(light.getRef(), transform.transform.getModelMatrix());
				}
			}

			// Objects
			{
				auto view = _registry.view<TransformComponent, MeshComponent>();
				for (auto entity : view) {
					auto [transform, mesh] = view.get<TransformComponent, MeshComponent>(entity);
					Renderer::submit(mesh.material, mesh.model, transform.transform.getModelMatrix());
				}
			}

			if (_skybox) {
				Renderer::submit(_skybox);
			}


			Renderer::endScene();
		}
	}

	void Scene::endScene() {
		// Destroy scripts
		{
			auto view = _registry.view<ScriptComponent>();
			for (auto entity : view) {
				auto& script = view.get<ScriptComponent>(entity);
				script.instance->onDestroy();
				script.destroyScript(&script);
			}
		}
	}


	void Scene::onViewportResize(uint32_t width, uint32_t height) {
		auto view = _registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			cameraComponent.camera.setViewportSize(width, height);
		}

	}

	Scene::~Scene() {

	}
}