#include "tuskpch.h"

#include "Animation.h"

namespace Tusk {
	Animation::Animation(float lengthInSeconds, const std::vector<Ref<KeyFrame>>& keyFrames) 
		: _length(lengthInSeconds), _keyFrames(keyFrames){}
}