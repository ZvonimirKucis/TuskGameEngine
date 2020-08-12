#include <Tusk.h>

class ExampleLayer : public Tusk::Layer {

public:
	ExampleLayer() : Layer("example") {
		const std::vector<Tusk::Vertex> vertices = {
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		const std::vector<uint32_t> indices = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		_vertexBuffer = Tusk::VertexBuffer::create(vertices);
		_indexBuffer = Tusk::IndexBuffer::create(indices);
		_shader = Tusk::Shader::create("assets/shaders/main.vert.spv", "assets/shaders/main.frag.spv");
		_texture = Tusk::Texture::create("assets/textures/statue.jpg");
	}

	void onUpdate() override {
		Tusk::Renderer::submit(_shader, _vertexBuffer, _indexBuffer, _texture);
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
	Tusk::Ref<Tusk::VertexBuffer> _vertexBuffer;
	Tusk::Ref<Tusk::IndexBuffer> _indexBuffer;
	Tusk::Ref<Tusk::Texture> _texture;
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