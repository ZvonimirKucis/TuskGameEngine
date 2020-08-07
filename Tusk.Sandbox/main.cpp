#include <Tusk.h>

class ExampleLayer : public Tusk::Layer {
public:
	ExampleLayer() : Layer("example") {
		_shader = Tusk::Shader::create("shaders/main.vert.spv", "shaders/main.frag.spv");
		_shader2 = Tusk::Shader::create("shaders/main.vert_2.spv", "shaders/main.frag.spv");
	}

	void onUpdate() override {
		Tusk::Renderer::beginScene();
		Tusk::Renderer::clear();
		Tusk::Renderer::submit(_shader);
		Tusk::Renderer::submit(_shader2);
		Tusk::Renderer::endScene();
	}

	void onEvent(Tusk::Event& event) override {
		if (event.getEventType() == Tusk::EventType::KeyPressed)
		{
			Tusk::KeyPressedEvent& e = (Tusk::KeyPressedEvent&)event;
			if (e.getKeyCode() == TUSK_KEY_TAB)
				Tusk::Logger::Log("Tab key is pressed!");
		}
	}
private:
	Tusk::Ref<Tusk::Shader> _shader;
	Tusk::Ref<Tusk::Shader> _shader2;
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