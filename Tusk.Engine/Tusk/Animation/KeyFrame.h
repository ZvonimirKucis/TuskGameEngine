#pragma once

#include "JointTransform.h"

namespace Tusk {
	class KeyFrame {
	public:
		KeyFrame(float timeStamp, const std::map<std::string, JointTransform>& pose);

		float getTimeStamp() { return _timeStamp; }
		std::map<std::string, JointTransform> getJointKeyFrames() { return _pose; }

	private:
		std::map<std::string, JointTransform> _pose;
		float _timeStamp;
	};
}