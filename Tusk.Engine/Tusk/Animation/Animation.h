#pragma once

#include "KeyFrame.h"

namespace Tusk {
	class Animation {
	public:
		Animation(float lengthInSeconds, const std::vector<Ref<KeyFrame>>& keyFrames);

		float getLength() { return _length; }
		std::vector<Ref<KeyFrame>> getKeyFrames() { return _keyFrames; }

	private:
		float _length;
		std::vector<Ref<KeyFrame>> _keyFrames;
	};
}