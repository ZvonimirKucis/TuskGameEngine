#include <Tusk.h>

class Sandbox : public Tusk::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Tusk::Application* Tusk::createApplication() {
	return new Sandbox();
}