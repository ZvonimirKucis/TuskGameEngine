#include <Tusk.h>

class ExampleLayer : public Tusk::Layer {

public:
	ExampleLayer() : Layer("example") {}

	void onAttach() override {
		/*_activeScene = new Tusk::Scene();
		_mesh = new Tusk::Mesh("assets/objects/viking_room.obj");

		_roomEntity = _activeScene->createEntity("room");
		_roomEntity.addComponent<Tusk::MeshComponent>(_mesh);*/
	}

	void onUpdate(float deltaTime) override {
		//_activeScene->onUpdate(deltaTime);
	}

	void onEvent(Tusk::Event& event) override {
		if (event.getEventType() == Tusk::EventType::KeyPressed)
		{
			Tusk::KeyPressedEvent& e = (Tusk::KeyPressedEvent&)event;
			if (e.getKeyCode() == TUSK_KEY_TAB)
				Tusk::Logger::Log("Tab key is pressed!");
		}
	}

	void onDetach() override {
	}

private:
	Tusk::Mesh* _mesh;

	Tusk::Scene* _activeScene;
	Tusk::Entity _roomEntity;
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