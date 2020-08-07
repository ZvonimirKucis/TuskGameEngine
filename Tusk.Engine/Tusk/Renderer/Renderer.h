#pragma once

#include "../Platform/Window.h"
#include "RendererCommand.h"
#include "RendererAPI.h"
#include "Shader.h"

namespace Tusk {

	class Renderer {
	public:
		static void init(const Ref<Window> window);
		static void clear();
		static void update();
		//static void Shutdown();

		//static void OnWindowResize(uint32_t width, uint32_t height);

		static void beginScene();
		static void endScene();

		static void submit(const Ref<Shader>& shader);
		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		//static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		/*struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};*/

		//static Scope<SceneData> s_SceneData;
	};
}