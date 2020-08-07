#pragma once

#include "../Input.h"

namespace Tusk {

	class GLFWInput : public Input {
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};
}