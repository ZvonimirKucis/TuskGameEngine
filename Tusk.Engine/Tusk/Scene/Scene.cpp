#include "tuskpch.h"

#include "../Renderer/Renderer.h"

#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace Tusk {

	Scene::Scene() {
		_shader = Tusk::Shader::create("assets/shaders/main.vert.spv", "assets/shaders/main.frag.spv");
		_texture = Tusk::Texture::create("assets/textures/viking_room.png");
	}

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
			_registry.view<ScriptComponent>().each([=](auto entity, auto& nsc)
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
				});
		}

		// Render
		{
			//auto view = _registry.view<TransformComponent, CameraComponent>();

			/*for (auto entity : view) {
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.primary) {

				}
			}*/

			Renderer::beginScene();
			Renderer::clear();
			auto view = _registry.view<TransformComponent, MeshComponent>();
			for (auto entity : view) {
				auto [transform, mesh] = view.get<TransformComponent, MeshComponent>(entity);
				
				Renderer::submit(_shader, mesh.mesh->getVertexBuffer(), mesh.mesh->getIndexBuffer(), _texture);
			}
			Renderer::endScene();
		}
	}

	Scene::~Scene() {

	}
}