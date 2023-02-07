#pragma once

#include "JointTransform.h"

namespace Tusk {
	class KeyFrame {
	public:
		KeyFrame(float timeStamp);

		float getTimeStamp() { return _timeStamp; }
		std::map<std::string, Ref<JointTransform>> getJointKeyFrames() { return _pose; }

		void addJointTransform(std::string jointName, Ref<JointTransform> transform);

	private:
		std::map<std::string, Ref<JointTransform>> _pose;
		float _timeStamp;
	};
}