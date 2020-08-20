#include "tuskpch.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {

	Scope<Renderer::SceneData> Renderer::_sceneData = CreateScope<Renderer::SceneData>();

	void Renderer::init() {
		RenderCommand::init();
	}

	void Renderer::shutdown() {
	}

	void Renderer::onWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::setViewport(0, 0, width, height);
	}

	void Renderer::beginScene() {
		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();
	}

	void Renderer::beginScene(const Camera& camera, const glm::mat4& transform, const DirectionalLight& lighData) {
		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();

		_sceneData->projection = camera.getProjection();
		_sceneData->view = glm::inverse(transform);
		_sceneData->lightData = lighData;
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(LightObject* lightObject, const glm::mat4& transform) {
		lightObject->draw(_sceneData->projection, _sceneData->view, transform);
	}

	void Renderer::submit(const Ref<Shader>& shader, const Ref<Model>& model, const glm::mat4& transform) {
		shader->bind();
		
		shader->setMat4("projection", _sceneData->projection);
		shader->setMat4("view", _sceneData->view);
		shader->setMat4("model", transform);


		shader->setFloat3("dirLight.direction",_sceneData->lightData.direction);
		shader->setFloat3("dirLight.ambient", _sceneData->lightData.ambient);
		shader->setFloat3("dirLight.diffuse", _sceneData->lightData.diffuse);
		shader->setFloat3("dirLight.specular", _sceneData->lightData.specular);

		model->draw(shader);
	}

}
