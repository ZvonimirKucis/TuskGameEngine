#pragma once

#if _WIN32 || _WIN64

extern Tusk::Application* Tusk::createApplication();

int main(int argc, char** argv) {
	auto app = Tusk::createApplication();
	app->run();
	delete app;

	return 0;
}

#endif
