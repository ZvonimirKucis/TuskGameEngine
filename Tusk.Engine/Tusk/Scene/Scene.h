#pragma once

#include "Tusk/Renderer/Shader.h"
#include "Tusk/Renderer/Texture.h"

#include "Tusk/Light/DirectionalLight.h"

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

		void startScene();
		void onUpdate(float deltaTime);
		void endScene();

		void onViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry _registry;
		uint32_t _viewportWidth = 0, _viewportHeight = 0;
		bool _renderLights = true;

		DirectionalLight _lightData;

		friend class Entity;
	};
}