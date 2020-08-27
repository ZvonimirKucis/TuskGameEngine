#include "tuskpch.h"

#include "KeyFrame.h"

namespace Tusk {
	KeyFrame::KeyFrame(float timeStamp, const std::map<std::string, JointTransform>& pose)
		:_timeStamp(timeStamp), _pose(pose){}
}