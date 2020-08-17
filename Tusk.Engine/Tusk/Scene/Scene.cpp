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

	void Scene::onUpdate(float deltaTime) {

		// Scripts
		{
			auto view = _registry.view<ScriptComponent>();
			for (auto entity : view) {
				auto& script = view.get<ScriptComponent>(entity);
				if (script.Instance == nullptr) {

					std::cout << "Created" << std::endl;
					std::cout << script.Instance << std::endl;

					script.instantiateFunction();
					std::cout << "Created 2" << std::endl;
					std::cout << script.Instance << std::endl;
					script.Instance->setEntity(Entity{ entity, this });
					std::cout << "Created 3" << std::endl;

					if (script.onCreateFunction)
						script.onCreateFunction(script.Instance);
				}

				if (script.onUpdateFunction)
					script.onUpdateFunction(script.Instance, deltaTime);
				
			}
			/*_registry.view<ScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.instance)
					{
						nsc.instantiateFunction();
						nsc.instance->_entity = Entity{ entity, this };

						if (nsc.onCreateFunction)
							nsc.onCreateFunction(nsc.instance);
					}

					if (nsc.onUpdateFunction)
						nsc.onUpdateFunction(nsc.instance, deltaTime);
				});*/
		}

		// Render
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = _registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.transform;
					break;
				}
			}
		}

		if(mainCamera)
		{
			Renderer::beginScene(*mainCamera, *cameraTransform);
			auto view = _registry.view<TransformComponent, MeshComponent>();
			for (auto entity : view) {
				auto [transform, mesh] = view.get<TransformComponent, MeshComponent>(entity);
				
				Renderer::submit(mesh.shader, mesh.model, transform.transform);
			}
			Renderer::endScene();
		}
	}

	void Scene::onViewportResize(uint32_t width, uint32_t height) {
		auto view = _registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			cameraComponent.Camera.setViewportSize(width, height);
		}

	}

	Scene::~Scene() {

	}
}