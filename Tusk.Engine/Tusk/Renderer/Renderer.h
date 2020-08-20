#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Tusk/Model/Model.h"
#include "Tusk/Camera/Camera.h"
#include "Tusk/Light/LightObject.h"
#include "Tusk/Light/DirectionalLight.h"
#include "Tusk/Skybox/Skybox.h"

namespace Tusk {

	class Renderer {
	public:
		static void init();
		static void shutdown();
		
		static void onWindowResize(uint32_t width, uint32_t height);

		static void beginScene();
		static void beginScene(const Camera& camera, const glm::mat4& transform, const DirectionalLight& lighData);
		static void endScene();

		static void submit(const Ref<Skybox>& skybox);
		static void submit(LightObject* lightObject, const glm::mat4& transform = glm::mat4(1.0f));
		static void submit(const Ref<Shader>& shader, const Ref<Model>& model, const glm::mat4& transform = glm::mat4(1.0f));
	private:
		struct SceneData {
			glm::mat4 projection;
			glm::mat4 view;
			DirectionalLight lightData;
		};

		static Scope<SceneData> _sceneData;
	};
}
