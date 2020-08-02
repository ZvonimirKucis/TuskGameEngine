#include "Engine.h"

int main() {
	Tusk::Engine* engine = new Tusk::Engine("Demo");
	engine->Run();

	delete engine;
	return 0;
}