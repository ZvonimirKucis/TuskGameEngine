#pragma once

#include <Tusk.h>
#include <imgui.h>

#include "../controllers/ModelController.h"
#include "../controllers/CameraController.h"


class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {}

	void onAttach() override {
		_activeScene = Tusk::CreateScope<Tusk::Scene>();

		_backpackModel = Tusk::CreateRef<Tusk::Model>("assets/objects/backpack/backpack.obj");
		_modelShader = Tusk::Shader::create("assets/shaders/model_loading.vs", "assets/shaders/model_loading.fs");

		_camera = _activeScene->createEntity("camera");
		_camera.addComponent<Tusk::CameraComponent>();
		_camera.addComponent<Tusk::ScriptComponent>().bind<Tusk::CameraController>();
		_activeScene->onViewportResize(Tusk::Application::get().getWindow().getWidth(), Tusk::Application::get().getWindow().getHeight());

		_modelEntity = _activeScene->createEntity("backpack");
		_modelEntity.addComponent<Tusk::MeshComponent>(_backpackModel, _modelShader);
		_modelEntity.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
		auto& transform = _modelEntity.getComponent<Tusk::TransformComponent>().transform;
		transform[3][0] = 5.0f;

		_modelEntityTest = _activeScene->createEntity("backpack_test");
		_modelEntityTest.addComponent<Tusk::MeshComponent>(_backpackModel, _modelShader);
		_modelEntityTest.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
		auto& transform2 = _modelEntityTest.getComponent<Tusk::TransformComponent>().transform;
		transform2[3][0] = -5.0f;
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
			_activeScene->onViewportResize(e.getWidth(), e.getHeight());
		}
	}

	void onDetach() override {
	}

private:
	Tusk::Ref<Tusk::Model> _backpackModel;
	Tusk::Ref<Tusk::Shader> _modelShader;

	Tusk::Scope<Tusk::Scene> _activeScene;

	Tusk::Entity _camera;
	Tusk::Entity _modelEntity;
	Tusk::Entity _modelEntityTest;
};