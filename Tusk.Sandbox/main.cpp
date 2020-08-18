#include <Tusk.h>
#include <Tusk/EntryPoint.h>

#include "layers/ExampleLayer.h"

class Sandbox : public Tusk::Application {
public:
	Sandbox() : Application("Tusk Sandbox - Zvonimir Kucis") {
		pushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

Tusk::Application* Tusk::createApplication() {
	return new Sandbox();
}