#include "tuskpch.h"

#include "Animation.h"

namespace Tusk {
	Animation::Animation(float lengthInSeconds, const std::vector<KeyFrame>& keyFrames) 
		: _length(lengthInSeconds), _keyFrames(keyFrames){}
}