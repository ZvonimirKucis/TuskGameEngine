#pragma once

#include "KeyFrame.h"

namespace Tusk {
	class Animation {
	public:
		Animation(float lengthInSeconds, const std::vector<KeyFrame>& keyFrames);

		float getLength() { return _length; }
		std::vector<KeyFrame> getKeyFrames() { return _keyFrames; }

	private:
		float _length;
		std::vector<KeyFrame> _keyFrames;
	};
}