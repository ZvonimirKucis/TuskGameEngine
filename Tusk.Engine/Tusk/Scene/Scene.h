#pragma once

#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

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

		void onUpdate(float deltaTime);
		void onViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry _registry;
		uint32_t _viewportWidth = 0, _viewportHeight = 0;
		bool _renderLights = true;

		friend class Entity;
	};
}