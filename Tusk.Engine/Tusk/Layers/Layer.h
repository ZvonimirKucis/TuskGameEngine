#pragma once
#include "../Utils/Defines.h"
#include "../Events/Event.h"

namespace Tusk {

	class TUSK_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		//virtual void OnImGuiRender() {}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return _debugName; }
	protected:
		std::string _debugName;
	};
}