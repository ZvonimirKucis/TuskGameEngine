#pragma once

#include <Tusk.h>
#include <imgui.h>

#include "../controllers/ModelController.h"
#include "../controllers/CameraController.h"


class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {}

	void onAttach() override {
		_runAnimation = Tusk::Loader::loadAnimation("assets/objects/model.dae");

		_playerModel = Tusk::CreateRef<Tusk::AnimationModel>("assets/objects/model.dae");
		_playerModel->playAnimation(_runAnimation);
		_playerShader = Tusk::Shader::load("assets/shaders/animation.vs", "assets/shaders/animation.fs");
		_playerMaterial = Tusk::CreateRef<Tusk::Material>(_playerShader);
		_playerMaterial->set2DTexture(Tusk::Texture2D::create("assets/objects/diffuse.png", Tusk::TextureType::Diffuse, true));
		
		_groundModel = Tusk::CreateRef<Tusk::Model>(Tusk::Primitive::instantiate(Tusk::PrimitiveType::Cube));
		_groundShader = Tusk::Shader::load("assets/shaders/blank.vs", "assets/shaders/blank.fs");
		_groundMaterial = Tusk::CreateRef<Tusk::Material>(_groundShader);

		_backpackModel = Tusk::CreateRef<Tusk::Model>("assets/objects/backpack/backpack.obj");
		_backpackShader = Tusk::Shader::load("assets/shaders/default.vs", "assets/shaders/default.fs");
		_backpackMaterial = Tusk::CreateRef<Tusk::Material>(_backpackShader);
		_backpackMaterial->set2DTexture(Tusk::Texture2D::create("assets/objects/backpack/diffuse.jpg", Tusk::TextureType::Diffuse, true));
		_backpackMaterial->set2DTexture(Tusk::Texture2D::create("assets/objects/backpack/normal.png", Tusk::TextureType::Normal, true));
		_backpackMaterial->set2DTexture(Tusk::Texture2D::create("assets/objects/backpack/specular.jpg", Tusk::TextureType::Specular, true));
		

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
		auto& cameraTransform = _cameraEntity.getComponent<Tusk::TransformComponent>().transform;
		cameraTransform.setPosition(glm::vec3(0.0f, 10.0f, 20.0f));
		_activeScene->onViewportResize(Tusk::Application::get().getWindow().getWidth(), Tusk::Application::get().getWindow().getHeight());

		_playerEntity = _activeScene->createEntity("player");
		_playerEntity.addComponent<Tusk::AnimatedMeshComponent>(_playerModel, _playerMaterial);
		auto& playerTransform = _playerEntity.getComponent<Tusk::TransformComponent>().transform;
		playerTransform.setPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
		playerTransform.setScale(1.5f);

		_backpackEntity = _activeScene->createEntity("backpack");
		_backpackEntity.addComponent<Tusk::MeshComponent>(_backpackModel, _backpackMaterial);
		_backpackEntity.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
		_backpackEntity.addComponent<Tusk::AudioSourceComponent>(Tusk::AudioSource::create());
		auto& transformTest = _backpackEntity.getComponent<Tusk::TransformComponent>().transform;
		transformTest.setPosition(glm::vec3(5.0f, 10.0f, -10.0f));
		transformTest.setScale(1.5f);

		_groundEntity = _activeScene->createEntity("ground");
		_groundEntity.addComponent<Tusk::MeshComponent>(_groundModel, _groundMaterial);
		auto& groundTransform = _groundEntity.getComponent<Tusk::TransformComponent>().transform;
		groundTransform.setPosition(glm::vec3(5.0f, 0.0f, -10.0f));
		groundTransform.setScale(glm::vec3(10.0f, 0.2f, 10.0f));
		
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
	Tusk::Scope<Tusk::Scene> _activeScene;

	Tusk::Ref<Tusk::AnimationModel> _playerModel;
	Tusk::Ref<Tusk::Animation> _runAnimation;
	Tusk::Ref<Tusk::AnimationModel> _animatedPlayerModel;
	Tusk::Ref<Tusk::Shader> _playerShader;
	Tusk::Ref<Tusk::Material> _playerMaterial;

	Tusk::Ref<Tusk::Model> _backpackModel;
	Tusk::Ref<Tusk::Shader> _backpackShader;
	Tusk::Ref<Tusk::Material> _backpackMaterial;

	Tusk::Ref<Tusk::Model> _groundModel;
	Tusk::Ref<Tusk::Shader> _groundShader;
	Tusk::Ref<Tusk::Material> _groundMaterial;

	//Tusk::Ref<Tusk::Shader> _envMappingShader;
	Tusk::Ref<Tusk::Skybox> _skybox;

	Tusk::Entity _cameraEntity;
	Tusk::Entity _lightEntity;
	Tusk::Entity _playerEntity;
	Tusk::Entity _backpackEntity;
	Tusk::Entity _groundEntity;
};