#pragma once

#include "Tusk/Layers/Layer.h"

namespace Tusk {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& e) override;

		void begin();
		void end();

		void blockEvents(bool block) { _blockEvents = block; }

	private:
		bool _blockEvents = true;
	};
}