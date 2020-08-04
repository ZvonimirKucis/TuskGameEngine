#include <Tusk.h>

class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {}

	void onUpdate() override {
		if (Tusk::Input::isKeyPressed(TUSK_KEY_TAB)) {
			Tusk::Logger::Log("Tab key is pressed (poll)!");
		}
	}

	void onEvent(Tusk::Event& event) override {
		Tusk::Logger::Log("Example layer, event: %s", event.toString().c_str());

		if (event.getEventType() == Tusk::EventType::KeyPressed)
		{
			Tusk::KeyPressedEvent& e = (Tusk::KeyPressedEvent&)event;
			if (e.getKeyCode() == TUSK_KEY_TAB)
				Tusk::Logger::Log("Tab key is pressed (event)!");
		}
	}
};

class Sandbox : public Tusk::Application {
public:
	Sandbox() {
		Tusk::Layer* layer = new ExampleLayer();
		Tusk::Logger::Log("Layer created: %s", layer->getName().c_str());
		
		pushLayer(layer);		
	}

	~Sandbox() {

	}
};

Tusk::Application* Tusk::createApplication() {
	return new Sandbox();
}