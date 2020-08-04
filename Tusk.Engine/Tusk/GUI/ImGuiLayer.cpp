#include "tuskpch.h"
#include "ImGuiLayer.h"

#include <ImGui/imgui.h>

namespace Tusk {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::onAttach() {
		//ImGui::CreateContext();
		//ImGui::StyleColorsDark();


	}

	void ImGuiLayer::onDetach() {

	}

	void ImGuiLayer::onUpdate() {

		//ImGui::Render();
	}

	void ImGuiLayer::onEvent(Event& event) {

	}
}