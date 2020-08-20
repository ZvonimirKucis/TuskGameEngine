#pragma once

#include <Tusk.h>
#include <imgui.h>

#include "../controllers/ModelController.h"
#include "../controllers/CameraController.h"


class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {}

	void onAttach() override {
		_backpackModel = Tusk::CreateRef<Tusk::Model>("assets/objects/backpack/backpack.obj");
		_modelShader = Tusk::Shader::load("assets/shaders/default.vs", "assets/shaders/default.fs");
		_envMappingShader = Tusk::Shader::load("assets/shaders/default_env_mapping.vs", "assets/shaders/default_env_mapping.fs");
		
		std::vector<std::string> faces = {
			"assets/skybox/right.jpg",
			"assets/skybox/left.jpg",
			"assets/skybox/top.jpg",
			"assets/skybox/bottom.jpg",
			"assets/skybox/front.jpg",
			"assets/skybox/back.jpg"
		};
		
		_skybox = Tusk::CreateRef<Tusk::Skybox>(faces);

		_activeScene = Tusk::CreateScope<Tusk::Scene>();
		_activeScene->renderLightObjects(false);
		_activeScene->setSkybox(_skybox);

		Tusk::DirectionalLight lightData = {};
		lightData.direction = glm::vec3(-2.0f, -3.0f, -4.0f);
		lightData.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		lightData.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		lightData.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		_lightEntity = _activeScene->createEntity("directional light");
		_lightEntity.addComponent<Tusk::DirectionalLightComponent>(lightData);

		_cameraEntity = _activeScene->createEntity("camera");
		_cameraEntity.addComponent<Tusk::CameraComponent>();
		_cameraEntity.addComponent<Tusk::ScriptComponent>().bind<Tusk::CameraController>();
		_activeScene->onViewportResize(Tusk::Application::get().getWindow().getWidth(), Tusk::Application::get().getWindow().getHeight());

		_modelEntity = _activeScene->createEntity("backpack");
		_modelEntity.addComponent<Tusk::MeshComponent>(_backpackModel, _envMappingShader);
		_modelEntity.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
		auto& transform = _modelEntity.getComponent<Tusk::TransformComponent>().transform;
		transform.setPosition(glm::vec3(-5.0f, 0.0f, -10.0f));
		transform.setScale(1.0f);

		_modelEntityTest = _activeScene->createEntity("backpack_test");
		_modelEntityTest.addComponent<Tusk::MeshComponent>(_backpackModel, _modelShader);
		_modelEntityTest.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
		auto& transformTest = _modelEntityTest.getComponent<Tusk::TransformComponent>().transform;
		transformTest.setPosition(glm::vec3(5.0f, 0.0f, -10.0f));
		transformTest.setScale(0.8f);

		_activeScene->startScene();
	}

	void onUpdate(float deltaTime) override {
		_activeScene->onUpdate(deltaTime);
	}

	void onImGuiRender(float deltaTime) override {
		ImGui::Begin("Stats");
		ImGui::Text("FPS: %.0f", 1 / deltaTime);
		ImGui::End();
	}

	void onEvent(Tusk::Event& event) override {
		if (event.getEventType() == Tusk::EventType::WindowResize) {
			Tusk::WindowResizeEvent& e = (Tusk::WindowResizeEvent&)event;
			if (e.getWidth() == 0 || e.getHeight() == 0)
				return;
			_activeScene->onViewportResize(e.getWidth(), e.getHeight());
		}
	}

	void onDetach() override {
		_activeScene->endScene();
	}

private:
	Tusk::Ref<Tusk::Model> _backpackModel;
	Tusk::Ref<Tusk::Shader> _modelShader;
	Tusk::Ref<Tusk::Shader> _envMappingShader;
	Tusk::Ref<Tusk::Skybox> _skybox;

	Tusk::Scope<Tusk::Scene> _activeScene;

	Tusk::Entity _cameraEntity;
	Tusk::Entity _lightEntity;
	Tusk::Entity _modelEntity;
	Tusk::Entity _modelEntityTest;
};