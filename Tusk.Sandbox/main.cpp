#include <Tusk.h>

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tusk {
	class CameraController : public ScriptableEntity {
	public:
		void onCreate() {
		}

		void onDestroy() {
		}

		void onUpdate(float ts) {
			auto& transform = getComponent<TransformComponent>().transform;
			float speed = 5.0f;

			if (Input::isKeyPressed(TUSK_KEY_A))
				transform[3][0] -= speed * ts;
			if (Input::isKeyPressed(TUSK_KEY_D))
				transform[3][0] += speed * ts;
			if (Input::isKeyPressed(TUSK_KEY_W))
				transform[3][1] += speed * ts;
			if (Input::isKeyPressed(TUSK_KEY_S))
				transform[3][1] -= speed * ts;
		}
	};
}

namespace Tusk {

	class ModelController : public ScriptableEntity {
	public:
		void onCreate() {
			auto& transform = getComponent<Tusk::TransformComponent>().transform;
			transform[3][2] = -10.0f;
		}

		void onDestroy() {
		}

		void onUpdate(float ts) {
			auto& transform = getComponent<Tusk::TransformComponent>().transform;
			transform = glm::rotate(transform, ts * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
	};
}


class ExampleLayer : public Tusk::Layer {

public:
	ExampleLayer() : Layer("example") {}

	void onAttach() override {
		_activeScene = Tusk::CreateScope<Tusk::Scene>();
		
		_backpackModel = Tusk::CreateRef<Tusk::Model>("assets/objects/backpack/backpack.obj");
		_modelShader = Tusk::Shader::create("assets/shaders/model_loading.vs", "assets/shaders/model_loading.fs");

		_camera = _activeScene->createEntity("camera");
		_camera.addComponent<Tusk::CameraComponent>();
		//_camera.addComponent<Tusk::ScriptComponent>().bind<Tusk::CameraController>();
		_activeScene->onViewportResize(Tusk::Application::get().getWindow().getWidth(), Tusk::Application::get().getWindow().getHeight());

		_modelEntity = _activeScene->createEntity("backpack");
		_modelEntity.addComponent<Tusk::MeshComponent>(_backpackModel, _modelShader);
		_modelEntity.addComponent<Tusk::ScriptComponent>().bind<Tusk::ModelController>();
	}

	void onUpdate(float deltaTime) override {
		_activeScene->onUpdate(deltaTime);
	}

	void onImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
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
};

class Sandbox : public Tusk::Application {
public:
	Sandbox() {
		pushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

Tusk::Application* Tusk::createApplication() {
	return new Sandbox();
}