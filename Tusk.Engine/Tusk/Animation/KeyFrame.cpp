#include "tuskpch.h"

#include "KeyFrame.h"

namespace Tusk {
	KeyFrame::KeyFrame(float timeStamp)
		:_timeStamp(timeStamp){}

	void KeyFrame::addJointTransform(std::string jointName, Ref<JointTransform> transform) {
		_pose.insert(std::pair<std::string, Ref<JointTransform>>{ jointName, transform });
	}
}