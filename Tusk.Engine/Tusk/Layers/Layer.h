#pragma once
#include "Tusk/Events/Event.h"

namespace Tusk {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onImGuiRender(float deltaTime) {}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return _debugName; }
	protected:
		std::string _debugName;
	};
}