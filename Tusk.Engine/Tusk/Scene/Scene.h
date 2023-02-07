#pragma once

#include "Tusk/Light/DirectionalLight.h"
#include "Tusk/Skybox/Skybox.h"

#include <entt.hpp>

namespace Tusk {
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity createEntity(const std::string& name = std::string());

		void renderLightObjects(bool value) { _renderLights = value; };
		void setSkybox(const Ref<Skybox>& skybox) { _skybox = skybox; }

		void startScene();
		void onUpdate(float deltaTime);
		void endScene();

		void onViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry _registry;
		uint32_t _viewportWidth = 0, _viewportHeight = 0;
		bool _renderLights = true;

		DirectionalLight _lightData;
		Ref<Skybox> _skybox;

		friend class Entity;
	};
}