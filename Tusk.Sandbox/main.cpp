#include <Tusk.h>

class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {}

	void onUpdate() override {
		Tusk::Logger::Log("Update");
	}

	void onEvent(Tusk::Event& event) override {
		Tusk::Logger::Log("layer, event: %s", event.ToString().c_str());
	}
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